#include "Enemy.hpp"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 8;
  m_current_sprite.ypu = 8;
  m_current_sprite.x = 0;
  m_current_sprite.y = 0;
  set_life(100, 100);

  m_interaction_box.offset = {4, 4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Enemy::fixed_update(double deltaTime) {
  Entity::fixed_update(deltaTime);
}

void Enemy::update(double deltaTime) {
  Entity::update(deltaTime);
}

void Enemy::post_update(double deltaTime) {
  Entity::post_update(deltaTime);
}

void Enemy::draw() {
  Entity::draw();
}


