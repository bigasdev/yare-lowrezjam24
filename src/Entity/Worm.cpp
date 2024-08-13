#include "Worm.hpp"
#include "../Core/App.hpp"
#include "../Core/Fort.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Tools/Cooldown.hpp"
#include "Projectile.hpp"
#include "../Utils/Gizmos.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include "UI/PlayerUI.hpp"

Worm::Worm() {}

Worm::~Worm() { delete this; }

void Worm::radial_shoot(int increase){
  for(int i = -360; i < 360; i += increase){
    auto projectile = g_fort->recruit<Projectile>(g_resources, g_atlas->get_game_scale());
    projectile->get_current_sprite()->texture = g_resources->get_aseprite_texture("concept");
    projectile->get_current_sprite()->xpu = 16;
    projectile->get_current_sprite()->ypu = 16;
    projectile->get_current_sprite()->x = 1;
    projectile->get_current_sprite()->y = 1;
    projectile->set_pos(m_pos.x, m_pos.y);
    projectile->init();
    projectile->set_speed(200);
    projectile->set_life(100, 100);
    projectile->set_friction(0.98f);
    projectile->move_dir({cosf(i), sinf(i)});
    projectile->set_angle(i);
  }
}

void Worm::walking_state(double deltaTime) {
  if(m_entity_cd->has_state("walking")) return;

  move_dir({rnd(-25.f,25.f), rnd(-25.f,25.f)});

  m_entity_cd->set_state("walking", 1.5f, [&]() {
      m_velocity = {0,0};
      change_state(BossState::INVICIBLE_STATE);
  });
}

void Worm::hit_state(double deltaTime) {
}

void Worm::invicible_state(double deltaTime) {
}

void Worm::rage_state(double deltaTime) {
}

void Worm::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 16;
  m_current_sprite.ypu = 16;
  m_current_sprite.x = 1;
  m_current_sprite.y = 1;
  set_life(100, 100);

  m_interaction_box.offset = {0, 0};
  m_interaction_box.scale = {16, 16};
  m_collision_box.scale = {16, 16};

  m_speed = 50;

  SpriteAnimation idle = SpriteAnimation{"idle", {1, 1}, 2, .5f,
                                         &m_current_sprite};
  add_sprite_animation(idle);
  set_animation("idle");
}
