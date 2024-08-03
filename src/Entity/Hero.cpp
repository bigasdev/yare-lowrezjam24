#include "Hero.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Camera.hpp"
#include "../Utils/Mouse.hpp"
#include "Projectile.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Core/InputManager.hpp"

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

  if(actions.interact){
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
    p->set_speed(500);
    p->init();

    auto angle = atan2(Mouse::get_mouse_pos().y - get_pos().y, Mouse::get_mouse_pos().x - get_pos().x);
    p->set_velocity({cos(-angle), sin(-angle)});
  }
  
  animation_manager();
}

void Hero::animation_manager(){
  if(actions.up || actions.down || actions.left || actions.right){
    set_animation("walk");
    return;
  }

  set_animation("idle");
}

void Hero::post_update(double deltaTime){
  Entity::post_update(deltaTime);
}
