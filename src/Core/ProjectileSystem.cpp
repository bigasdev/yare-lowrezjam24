#include "ProjectileSystem.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Resources/Resources.hpp"
#include "../Utils/FDebug.hpp"
#include "../Entity/Projectile.hpp"

ProjectileSystem::ProjectileSystem() {}

ProjectileSystem::ProjectileSystem(Fort *fort, Atlas *atlas,
                                   Resources *resources,
                                   std::vector<Projectile *> *projectiles, Entity **hero) {
  m_fort = fort;
  m_atlas = atlas;
  m_resources = resources;
  m_projectiles = projectiles;
  m_hero = *hero;
}

ProjectileSystem::~ProjectileSystem() {}

void ProjectileSystem::shoot_front(vec2f pos, ProjectileTag _tag) {
  auto t = m_fort->recruit<Projectile>(m_resources, m_atlas->get_game_scale());
  t->get_current_sprite()->texture =
      m_resources->get_aseprite_texture("enemy_atlas");
  t->set_pos(pos.x + 125, pos.y + 125);
  t->get_current_sprite()->x = 0;
  t->get_current_sprite()->y = 2;
  t->get_current_sprite()->xpu = 9;
  t->get_current_sprite()->ypu = 9;
  t->set_tag(_tag);

  t->set_collision_box({{2, 2}, {8, 8}});

  auto angle = 0.8f;
  auto velocity_x = 1300 * cos(angle);
  auto velocity_y = 1300 * sin(angle);
  t->reset();
  t->set_velocity({velocity_x, velocity_y});
  t->set_angle(angle * 180 / 3.14159265);
  t->add_hero(&m_hero);
  m_projectiles->push_back(std::move(t));
}

void ProjectileSystem::shoot_at(vec2f pos, Entity *en, ProjectileTag _tag) {
  auto t = m_fort->recruit<Projectile>(m_resources, m_atlas->get_game_scale());
  t->get_current_sprite()->texture =
      m_resources->get_aseprite_texture("enemy_atlas");
  t->set_pos(pos.x, pos.y);
  t->get_current_sprite()->x = 0;
  t->get_current_sprite()->y = 2;
  t->get_current_sprite()->xpu = 9;
  t->get_current_sprite()->ypu = 9;
  t->set_tag(_tag);

  t->set_collision_box({{2, 2}, {8, 8}});

  auto angle = atan2(en->get_pos().y - t->get_pos().y,
                     en->get_pos().x - t->get_pos().x);
  auto velocity_x = 700 * cos(angle);
  auto velocity_y = 700 * sin(angle);
  t->reset();
  t->set_velocity({velocity_x, velocity_y});
  t->set_speed(.5f);
  t->set_friction(1);
  t->add_hero(&m_hero);
  m_projectiles->push_back(std::move(t));
}
