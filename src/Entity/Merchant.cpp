#include "Merchant.hpp"
#include "../Core/App.hpp"
#include "UI/PlayerUI.hpp"
#include "../Renderer/Camera.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Gizmos.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include <string>

Merchant::Merchant() {}

Merchant::~Merchant() {}

void Merchant::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 8;
  m_current_sprite.ypu = 8;
  m_current_sprite.x = 0;
  m_current_sprite.y = 3;
  set_life(100, 100);

  m_interaction_box.offset = {0, 0};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Merchant::fixed_update(double deltaTime) {
  if (is_interacting(g_hero) && !shuffling_state) {
    interact_range = true;

    if (g_hero->has_interact()) {
      if(g_hero->get_inventory()->coins <= 25){
        g_player_ui->set_dialogue("Need 25 coins!");
      }else{
        g_hero->get_inventory()->coins -= 25;
        shuffling_state = true;
      }
    }
  } else {
    interact_range = false;
  }

  if(shuffling_state && shuffle_ticks < SHUFFLE_TICKS){
    if(!m_entity_cd->has_state("shuffle")){
      m_entity_cd->set_state("shuffle", SHUFFLE_CD);

      shuffled_amt = d20();

      shuffle_ticks++;
      g_camera->set_shake(5.f, .1f);
      if(shuffle_ticks == SHUFFLE_TICKS){
        m_entity_cd->set_state("end_shuffle", 1.5f, [&](){
          g_camera->set_shake(50.5f, .05f);
          shuffling_state = false;

        });
      }
    }
  }
}

void Merchant::update(double deltaTime) {
  Entity::update(deltaTime);
}

void Merchant::draw() {
  Entity::draw();

  if(shuffling_state){
    g_atlas->draw_text(get_pos() + vec2f{2,-4}, std::to_string(shuffled_amt).c_str(), g_app->get_main_font(), {255, 255, 255}, 1, 128, g_camera);
  }
}

void Merchant::post_update(double deltaTime) {
  Entity::post_update(deltaTime);
}

