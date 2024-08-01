#pragma once
#ifndef PROJECTILE_SYSTEM_HPP
#define PROJECTILE_SYSTEM_HPP

#include "Fort.hpp"
#include <vector>

class Atlas;
class Resources;
class Entity;

class ProjectileSystem{
  public:
    ProjectileSystem();
    ProjectileSystem(Fort* fort, Atlas* atlas, Resources* resources, std::vector<Projectile*>* projectiles, Entity** hero);
    ~ProjectileSystem();

    void shoot_front(vec2f pos, ProjectileTag _tag = PROJECTILE_ENEMY);
    void shoot_at(vec2f pos, Entity* en, ProjectileTag _tag = PROJECTILE_ENEMY);

  private:
    Fort* m_fort;
    Atlas* m_atlas;
    Resources* m_resources;
    std::vector<Projectile*>* m_projectiles;
    Entity* m_hero;
};

#endif
