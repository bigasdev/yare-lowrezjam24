#include "MainScene.hpp"
#include "../Utils/Gizmos.hpp"
#include "../Utils/PixelDrawer.hpp"

#include "../Core/App.hpp"
#include "../Utils/Math.hpp"
#include "../Entity/Item.hpp"
#include "../Entity/Projectile.hpp"
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
#include "../Scenes/GameScene.hpp"
#include "SDL_keycode.h"
#include <string>

InputManager *main_input_manager = nullptr;
GameScene *game_scene = nullptr;

bool change_scene = false;
bool mouse_press = false;

struct MenuOption {
  std::string name;
  float x;
  float *y;
};

std::vector<MenuOption> options;

MainScene::MainScene(App *app, Logger *logger, Cooldown *cooldown,
                     Camera *camera)
    : Scene(app, logger, cooldown, camera) {
  game_scene = new GameScene(app, logger, cooldown, camera);
}

// Load assets is mainly used to load the entities and textures we might need
// It's the last thing to run on the init function, so don't use/instantiate
// variables here if possible
void MainScene::load_assets() {}

// This is where all the classes should be instantiated, this is the place where
// we can setup stuff too.
void MainScene::init() {
  main_input_manager = new InputManager();
  //
  load_assets();
  //
  main_input_manager->bind_keyboard(SDLK_e, &change_scene);
  main_input_manager->bind_mouse(&mouse_press, &mouse_press, &mouse_press);

  MenuOption play;
  play.name = "Play";
  play.x = 20;
  play.y = m_app->get_window_y();
  options.push_back(play);
}

void MainScene::update(double deltaTime) {
  if (change_scene)
    g_app->change_scene(game_scene);

  for (auto &option : options) {
    if (Mouse::is_at_area(
            {20, *option.y - (*option.y / 2 + 100), 200, 50})) {
      if (mouse_press) {
        g_app->change_scene(game_scene);
      }

      option.x = Math::move_to(option.x, 23, 25.5f * deltaTime);
    }else{
      option.x = Math::lerp(option.x, 20, 12.f * deltaTime);
    }
  }
}

void MainScene::post_update(double deltaTime) {}

bool enable_collision_box = false;
void MainScene::draw() {
#if F_ENABLE_IMGUI
  GUI::draw([this]() { this->ui(); });
#endif

  for (auto &option : options) {
    m_atlas->draw_text({option.x, *option.y - (*option.y / 2 + 100)},
                       option.name.c_str(), m_app->get_main_font(),
                       {255, 255, 255, 255}, 2.f);
  }

  m_atlas->draw_text({10, m_app->get_window_size().y - 30},
                     "@bigasdev v0.1 powered by fortress framework!",
                     m_app->get_main_font(), {255, 255, 255, 255}, 1.f);
}

// This is where the Dear ImGui "update" is called, add any function with imgui
// stuff here to display on screen
void MainScene::ui() {
#if F_ENABLE_DEBUG
#endif
}

void MainScene::input(SDL_Event event) { main_input_manager->update(event); }

void MainScene::clean() {}
