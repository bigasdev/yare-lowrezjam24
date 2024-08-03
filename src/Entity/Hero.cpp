#include "Hero.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Camera.hpp"
#include "../Utils/Mouse.hpp"
#include "Projectile.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Core/InputManager.hpp"
#include "../Tools/Cooldown.hpp"

Hero::Hero(){
}

Hero::~Hero(){
  Entity::~Entity();
}

void Hero::init(){
  Entity::init();

  actions = {false,false,false,false,false,false,false};
}

void Hero::fixed_update(double deltaTime){
  m_pos += (g_input_manager->get_raw_axis() * m_speed) * deltaTime;
}

void Hero::update(double deltaTime){
  Entity::update(deltaTime);

  if(actions.interact && !m_entity_cd->has_state("attack")){
    auto p = g_fort->recruit<Projectile>(g_resources, g_camera->s_scale);
    p->get_current_sprite()->texture = get_current_sprite()->texture;
    p->set_pos(get_pos().x + 5, get_pos().y);
    p->get_current_sprite()->xpu = 8;
    p->get_current_sprite()->ypu = 8;
    p->get_current_sprite()->x = 0;
    p->get_current_sprite()->y = 5;
    p->set_life(100,100);
    p->set_tag(ProjectileTag::PROJECTILE_HERO);
    p->set_collision_box({{2, 2}, {10, 11}});
    p->set_speed(250);
    p->init();

    auto angle = atan2(Mouse::get_mouse_pos().y - get_pos().y, Mouse::get_mouse_pos().x - get_pos().x);
    if(g_input_manager->get_right_axis() != vec2f(0,0)){
      angle = atan2(g_input_manager->get_right_axis().y, g_input_manager->get_right_axis().x);
    }
    p->set_velocity({cos(angle), sin(angle)});

    m_entity_cd->set_state("attack", 5.f);
  }
  
  animation_manager();
}

void Hero::animation_manager(){
  if(g_input_manager->get_raw_axis().x == 1 || g_input_manager->get_right_axis().x == 1){
    m_current_sprite.facing_right = true;
  }
  if(g_input_manager->get_raw_axis().x == -1 || g_input_manager->get_right_axis().x == -1){
    m_current_sprite.facing_right = false;
  }

  if(g_input_manager->get_raw_axis() != vec2f(0,0)){
    set_animation("walk");
    return;
  }

  set_animation("idle");
}

void Hero::post_update(double deltaTime){
  Entity::post_update(deltaTime);
}
