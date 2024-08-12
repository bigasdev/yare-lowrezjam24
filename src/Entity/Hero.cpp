#include "Hero.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Core/InputManager.hpp"
#include "../Renderer/Camera.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Gizmos.hpp"
#include "../Utils/Mouse.hpp"
#include "Projectile.hpp"
#include "Room.hpp"

bool can_move = true;

Hero::Hero() {}

Hero::~Hero() { Entity::~Entity(); }

void Hero::init() {
  Entity::init();

  actions = {false, false, false, false, false, false, false};

  m_interaction_box.offset = {0, 0};
  m_interaction_box.scale = {15, 15};
  m_speed = 50;

  inventory.coins = 50;
}

bool Hero::is_moving() { return !g_input_manager->get_raw_axis().zero(); }

void Hero::fixed_update(double deltaTime) {
  if (can_move) {
    if((m_pos + (g_input_manager->get_raw_axis() * m_speed) * deltaTime).x < -g_grid.x/2 || (m_pos + (g_input_manager->get_raw_axis() * m_speed) * deltaTime).x > g_grid.x || (m_pos + (g_input_manager->get_raw_axis() * m_speed) * deltaTime).y < -g_grid.y/2 || (m_pos + (g_input_manager->get_raw_axis() * m_speed) * deltaTime).y > g_grid.y){
      if(g_hero_state == HeroState::FARM)return;
    }

    m_pos += (g_input_manager->get_raw_axis() * m_speed) * deltaTime;
  }
}

void Hero::update(double deltaTime) {
  Entity::update(deltaTime);
  can_move = true;

  if (is_moving()) {
    for (auto &prop : *g_collider_tiles) {
      CollisionBox2D box = get_interaction_box();
      box.offset = get_pos() + g_input_manager->get_raw_axis() * 3;

      CollisionBox2D prop_box;
      if (get_pos().y < prop.y) {
        prop_box.offset = {static_cast<float>(prop.x),
                           static_cast<float>(prop.y + 2)};
      } else {
        prop_box.offset = {static_cast<float>(prop.x),
                           static_cast<float>(prop.y) - 8};
      }
      prop_box.scale = prop.collision.scale;

      if (is_colliding(box, prop_box)) {
        can_move = false;
      }
    }
  }

  if (g_input_manager->get_raw_axis() != vec2f(0, 0)) {
    m_current_sprite.facing_right = g_input_manager->get_raw_axis().x == 1;

    if (!m_entity_cd->has_state("dust")) {
      g_particle_system->walk_dust(get_pos());

      m_entity_cd->set_state("dust", 5.f);
    }
  }

  if (actions.attack && !m_entity_cd->has_state("attack")) {
    g_camera->set_entity(nullptr);
    auto p = g_fort->recruit<Projectile>(g_resources, g_camera->s_scale);
    p->get_current_sprite()->texture = get_current_sprite()->texture;
    p->set_pos(get_pos().x + 5, get_pos().y);
    p->get_current_sprite()->xpu = 8;
    p->get_current_sprite()->ypu = 8;
    p->get_current_sprite()->x = 0;
    p->get_current_sprite()->y = 5;
    p->set_life(100, 100);
    p->set_tag(ProjectileTag::PROJECTILE_HERO);
    p->set_collision_box({{2, 2}, {10, 11}});
    p->set_speed(250);
    p->init();

    auto angle = atan2(Mouse::get_mouse_pos().y - get_pos().y,
                       Mouse::get_mouse_pos().x - get_pos().x);
    if (g_input_manager->get_right_axis() != vec2f(0, 0)) {
      angle = atan2(g_input_manager->get_right_axis().y,
                    g_input_manager->get_right_axis().x);
    }
    p->set_velocity({cos(angle), sin(angle)});

    m_entity_cd->set_state("attack", 5.f);
  }

  animation_manager();
}

void Hero::draw() {
  Entity::draw();
#if F_ENABLE_DEBUG
  /*Gizmos::draw_rect(get_interaction_box().offset, get_interaction_box().scale,
                    g_atlas, {255, 0, 0}, 85, g_camera);
  if(is_moving()){
    Gizmos::draw_rect(get_pos() + g_input_manager->get_raw_axis() * 3,
  get_interaction_box().scale, g_atlas, {0,255,0}, 125, g_camera);
  }*/
#endif
}

void Hero::animation_manager() {
  if (g_input_manager->get_raw_axis().x == 1 ||
      g_input_manager->get_right_axis().x == 1) {
    m_current_sprite.facing_right = true;
  }
  if (g_input_manager->get_raw_axis().x == -1 ||
      g_input_manager->get_right_axis().x == -1) {
    m_current_sprite.facing_right = false;
  }

  if (g_input_manager->get_raw_axis() != vec2f(0, 0)) {
    set_animation("walk");
    return;
  }

  set_animation("idle");
}

void Hero::post_update(double deltaTime) { Entity::post_update(deltaTime); }
