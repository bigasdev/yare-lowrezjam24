#include "Dirt.hpp"
#include "../Core/Globals.hpp"
#include "../Core/App.hpp"
#include "UI/PlayerUI.hpp"
#include "UI/EntityTooltips.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Gizmos.hpp"
#include "../Core/SoundManager.hpp" 
#include "EntityParty.hpp"
#include "Hero.hpp"
#include <string>

Dirt::Dirt() {}

Dirt::~Dirt() {}

void Dirt::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 8;
  m_current_sprite.ypu = 8;
  m_current_sprite.x = 0;
  m_current_sprite.y = 2;
  set_life(100, 100);

  m_interaction_box.offset = {4, 4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};

  plant_state = 0;
}

void Dirt::fixed_update(double deltaTime) {
  if (is_interacting(g_hero)) {
    interact_range = true;

    if (g_hero->has_interact()) {
      if (!has_plant) {
        g_sound_manager->play_sound("planting");
        g_particle_system->plant_carrot(get_pos());
        has_plant = true;
      }else{
        if(plant_state >= 10){
          g_hero_state = HeroState::BATTLE;
          g_sound_manager->play_sound("entering");
          g_hero->set_pos(500, 500);
          has_plant = false;
          g_last_pos = get_pos();
        }
      }
    }
  } else {
    interact_range = false;
  }
}

void Dirt::update(double deltaTime) {
  Entity::update(deltaTime);

  if (!m_entity_cd->has_state("plant_grown") && has_plant) {
    m_entity_cd->set_state("plant_grown", PLANT_CD);

    plant_state++;

    if(plant_state >= 10 && has_planted_info == false){
      g_player_ui->set_dialogue("Harvest the crop");
      has_planted_info = true;
    }
  }
}

void Dirt::draw() {
#if F_ENABLE_DEBUG
  Gizmos::draw_rect(get_interaction_box().offset, get_interaction_box().scale,
                    g_atlas, {255, 0, 0}, 85, g_camera);
#endif
  if (interact_range) {
    m_tooltip->draw(*get_current_sprite()->texture, get_pos() + vec2f{4, -16});
  }

  if (has_plant) {
    m_atlas->draw_texture_from_sheet(*m_current_sprite.texture,
                                     get_pos() + vec2f(0, -4), {8, 8, 0, 3},
                                     g_camera);
    if (plant_state <= 10) {
      m_atlas->draw_line(get_pos() + vec2f(-2, 16),
                         get_pos() + vec2f(plant_state, 16), {0, 255, 0}, 255,
                         g_camera, 0, 2);
      m_atlas->draw_line(get_pos() + vec2f(-2, 17),
                         get_pos() + vec2f(plant_state, 17), {0, 255, 0}, 255,
                         g_camera, 0, 2);
    }
  }
}

void Dirt::post_update(double deltaTime) {}

void Dirt::animation_manager() {}
