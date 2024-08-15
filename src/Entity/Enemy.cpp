#include "Enemy.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Atlas.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include "Item.hpp"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::init() {
  Entity::init();
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 16;
  m_current_sprite.ypu = 16;
  m_current_sprite.x = 0;
  m_current_sprite.y = 10;
  set_life(100, 100);

  m_interaction_box.offset = {4, 4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Enemy::fixed_update(double deltaTime) { Entity::fixed_update(deltaTime); }

void Enemy::update(double deltaTime) {
  Entity::update(deltaTime);

  move_to(g_hero);
}

void Enemy::post_update(double deltaTime) { Entity::post_update(deltaTime); }

void Enemy::draw() { Entity::draw(); }

void Enemy::kill() {
  Entity::kill();
  F_Debug::log("Enemy killed");

  auto r = rnd(2, 6);
  for (int i = 0; i < r; i++) {
    auto coin = g_fort->recruit<Item>(g_resources, g_atlas->get_game_scale());
    coin->set_pos(get_pos().x + rnd(-5, 5), get_pos().y);
    coin->init();
    coin->set_speed(200);
    coin->set_life(100, 100);
    coin->set_friction(0.98f);
    coin->move_dir({rnd(-15.f, 15.f), rnd(-15.f, 15.f)});
    coin->set_coin();
  }
}
