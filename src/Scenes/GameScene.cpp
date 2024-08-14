#include "GameScene.hpp"

#include "../Utils/Gizmos.hpp"
#include "../Utils/PixelDrawer.hpp"

#include "../Core/App.hpp"
#include "../Entity/Hero.hpp"
#include "../Entity/Dirt.hpp"
#include "../Entity/Worm.hpp"
#include "../Entity/Item.hpp"
#include "../Entity/Projectile.hpp"
#include "../Core/SoundManager.hpp"
#include "../Entity/Merchant.hpp"
#include "../Entity/UI/PlayerUI.hpp"
#include "../Entity/Room.hpp"
#include <algorithm>
#include <memory>
#if F_ENABLE_IMGUI
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_sdl.h"
#endif
#include "../Renderer/AppGui.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Mouse.hpp"

#include "../Core/Fort.hpp"
#include "../Core/GarbageCollector.hpp"
#include "../Core/Globals.hpp"
#include "../Core/InputManager.hpp"
#include "../Core/ProjectileSystem.hpp"
#include "../Renderer/LightSystem.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "SDL_keycode.h"
#include "UIPartialScene.hpp"
#include <string>

UIPartialScene *ui_partial_scene;

// Castle db converter
CastleDBConverter *m_castle_db;

// Input
InputManager *m_input_manager = nullptr;

// GarbageCollector
GarbageCollector *m_garbage_collector = nullptr;

// Entity stuff
Fort *m_fort = nullptr;
ProjectileSystem *m_projectile_system = nullptr;
Hero *m_hero = nullptr;
Room *m_room = nullptr;
PlayerUI *m_player_ui = nullptr;
std::vector<Entity *> visible_entities;
std::vector<Entity *> visible_enemies;

// Polish
ParticleSystem *m_particle_system = nullptr;
LightSystem *m_light_system = nullptr;

// Test purpouses
// FIX: always remember to remove stuff from here

GameScene::GameScene(App *app, Logger *logger, Cooldown *cooldown,
                     Camera *camera)
    : Scene(app, logger, cooldown, camera) {}

// Load assets is mainly used to load the entities and textures we might need
// It's the last thing to run on the init function, so don't use/instantiate
// variables here if possible
void GameScene::load_assets() {
  // tileset stuff
  m_room = new Room({1200, 400}, {30, 30});

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      auto d = m_fort->recruit<Dirt>(m_resources, m_atlas->get_game_scale());
      d->set_pos(70 + i*25, 70 + j*25);
      d->init();
    }
  }

  auto hero = m_fort->recruit<Hero>(m_resources, m_atlas->get_game_scale());

  hero->get_current_sprite()->texture =
      m_resources->get_aseprite_texture("concept");
  hero->set_pos(35, 50);

  hero->get_current_sprite()->xpu = 7;
  hero->get_current_sprite()->ypu = 8;
  hero->get_current_sprite()->x = 0;
  hero->get_current_sprite()->y = 1;
  hero->set_life(100, 100);
  hero->m_tag = Tag::HERO;
  hero->set_collision_box({{2, 2}, {10, 11}});
  hero->set_speed(50);
  hero->init();
  g_hero = hero;

  auto merchant = m_fort->recruit<Merchant>(m_resources, m_atlas->get_game_scale());
  merchant->set_pos(45, -10);
  merchant->init();

  /*for(int i = 0; i < 1000; i++){
    auto e = m_fort->recruit<Entity>(m_resources, m_atlas->get_game_scale());
    e->set_pos(1200 + rnd(-1900, 1900), 400 + rnd(-1900, 1900));
    e->get_current_sprite()->texture =
        m_resources->get_aseprite_texture("character_atlas");
    e->get_current_sprite()->xpu = 11;
    e->get_current_sprite()->ypu = 12;
    e->get_current_sprite()->x = 1;
    e->get_current_sprite()->y = 0;
    e->set_life(100, 100);
    e->m_tag = Tag::ENEMY;
    e->set_collision_box({{2, 2}, {10, 11}});
    e->init();
  }*/
}

void GameScene::init() {

  m_app->change_background_color(vec3f(0, 0, 0));
  m_input_manager = new InputManager();
  m_garbage_collector = new GarbageCollector();

  m_fort = new Fort();
  m_player_ui = new PlayerUI();

  m_particle_system = new ParticleSystem(m_atlas, m_camera, 1000);
  m_light_system = new LightSystem(1000);
  //
  g_fort = m_fort;
  g_projectile_system = m_projectile_system;
  g_particle_system = m_particle_system;
  g_input_manager = m_input_manager;
  g_ALL = &visible_entities;
  g_enemies = &visible_enemies;
  g_player_ui = m_player_ui;
  // example of castle db loading
  load_assets();


  //
  ui_partial_scene = new UIPartialScene(m_app, m_logger, m_cd, m_camera);

  // input keyboard
  m_input_manager->bind_keyboard(SDLK_w, &g_hero->actions.up);
  m_input_manager->bind_keyboard(SDLK_s, &g_hero->actions.down);
  m_input_manager->bind_keyboard(SDLK_a, &g_hero->actions.left);
  m_input_manager->bind_keyboard(SDLK_d, &g_hero->actions.right);
  m_input_manager->bind_keyboard(SDLK_e, &g_hero->actions.interact);
  m_input_manager->bind_keyboard(SDLK_SOFTLEFT, &g_hero->actions.roll);

  m_input_manager->bind_mouse(&g_hero->actions.attack, nullptr, nullptr);

  //input controller 
  m_input_manager->bind_joy(JoyInput::RIGHT_TRIGGER, &g_hero->actions.interact);

  //tutorial and stuff 
}

void GameScene::fixed_update(double deltaTime) {
}


void GameScene::update(double deltaTime) {
  m_cd->update(deltaTime);

  m_particle_system->update(deltaTime);
  m_light_system->update(deltaTime);
  m_player_ui->update(deltaTime);

  ui_partial_scene->update(deltaTime);
  if(!m_cd->has_state("update_drawing")){
    m_cd->set_state("update_drawing", 0.1f, [this](){
    });
    visible_entities.clear();
    std::copy_if(m_fort->party().begin(), m_fort->party().end(),
                 std::back_inserter(visible_entities),
                 [](Entity *e) { return e->is_visible(); });
    visible_enemies.clear();
    std::copy_if(m_fort->party().begin(), m_fort->party().end(),
                 std::back_inserter(visible_enemies),
                 [](Entity *e) { return e->is_visible() && e->m_tag == Tag::ENEMY; });
  }

  if(!m_cd->has_state("snow")){
    /*m_particle_system->snow_dust({0,0});

    m_cd->set_state("snow", rnd(400, 602));*/
  }

  for (auto &e : visible_entities) {
    e->fixed_update(deltaTime);
    e->update(deltaTime);
  }



#if F_ENABLE_DEBUG
  /*
  if(m_castle_db->update("res/data/enemies.json")){

  }*/
#endif
}

void GameScene::post_update(double deltaTime) {
  m_camera->move(deltaTime);
  m_camera->update(deltaTime);
  m_garbage_collector->update();
}

void GameScene::ui() {}

void GameScene::draw() {
  // ui
#if F_ENABLE_IMGUI
  GUI::draw([this]() { this->ui(); });
#endif
  m_room->draw();

  for (auto &e : visible_entities) {
    m_atlas->draw_from_sheet(e, m_camera);
  }

  for(auto &e : visible_entities){
    e->draw();
  }

  m_room->post_draw();

  m_particle_system->draw();
  m_light_system->draw(m_atlas, m_camera);

  ui_partial_scene->draw();
  m_player_ui->draw();

  if(is_paused){
    g_atlas->draw_screen_filter(0,0,0,125,0);
    g_atlas->draw_text({16, 8}, "PAUSED", g_app->get_main_font(), {255, 255, 255}, 1, 128, nullptr);
  }
}

void GameScene::input(SDL_Event event) {
  ui_partial_scene->input(event);

  m_input_manager->update(event);
}

void GameScene::clean() {
  m_fort->destroy();
  delete m_input_manager;
  delete m_garbage_collector;
  delete m_fort;
  delete m_projectile_system;
  delete m_particle_system;
  delete m_light_system;
}
