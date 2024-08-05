#include "Dirt.hpp"
#include "EntityParty.hpp"
#include "../Utils/Gizmos.hpp"

Dirt::Dirt() {}

Dirt::~Dirt() {}

void Dirt::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 8;
  m_current_sprite.ypu = 8;
  m_current_sprite.x = 0;
  m_current_sprite.y = 2;
  set_life(100, 100);

  m_interaction_box.scale = {16,16};
}

void Dirt::fixed_update(double deltaTime) {}

void Dirt::update(double deltaTime) {
  Entity::update(deltaTime);
}


void Dirt::draw() {
#if F_ENABLE_DEBUG
  Gizmos::draw_rect(get_pos() + get_interaction_box().offset, get_interaction_box().scale, g_atlas, {255, 0, 0}, 85, g_camera);
#endif
}

void Dirt::post_update(double deltaTime) {}

void Dirt::animation_manager() {}
