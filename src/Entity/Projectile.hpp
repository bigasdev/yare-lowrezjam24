#pragma once
#include "Entity.hpp"

class ParticleSystem;

class Projectile : public Entity {
public:
  Projectile();
  Projectile(Resources *_res, float _scale);
  ~Projectile();

  void fixed_update(double deltaTime) override;
  void update(double deltaTime);

  // setters
  void set_velocity(vec2f _velocity) { m_velocity = _velocity; }
  void reset();
  void add_mobs(std::vector<Entity *> *_entities) { m_entities = _entities; }
  void add_hero(Entity **_hero) { l_hero = *_hero; }
  void set_particle_system(ParticleSystem *_particle_system) {
    m_particle_system = _particle_system;
  }
  void set_tag(ProjectileTag _tag) { b_tag = _tag; }

  // getters
  float get_life_time() { return lifeTime; }

private:
  float lifeTime = 1;
  std::vector<Entity *> *m_entities;
  ProjectileTag b_tag = PROJECTILE_HERO;
  Entity* l_hero;

  ParticleSystem *m_particle_system;
};
