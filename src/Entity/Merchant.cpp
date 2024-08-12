#include "Merchant.hpp"
#include "../Core/App.hpp"
#include "UI/PlayerUI.hpp"
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
  if (is_interacting(g_hero)) {
    interact_range = true;

    if (g_hero->has_interact()) {
      if(g_hero->get_inventory()->coins <= 25){
        g_player_ui->set_dialogue("Need more coins!");
      }
    }
  } else {
    interact_range = false;
  }
}

void Merchant::update(double deltaTime) {
  Entity::update(deltaTime);
}

void Merchant::draw() {
  Entity::draw();
}

void Merchant::post_update(double deltaTime) {
  Entity::post_update(deltaTime);
}

