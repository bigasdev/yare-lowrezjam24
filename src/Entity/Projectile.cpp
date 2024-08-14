#include "Projectile.hpp"
#include "../Utils/Math.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "EntityParty.hpp"
#include "../Entity/Hero.hpp"

Projectile::Projectile() {}

Projectile::~Projectile() { delete this; }

void Projectile::reset() {
  m_speed = 0.5f;
  m_friction = .94f;
  lifeTime = 1;
}

void Projectile::fixed_update(double deltaTime) {
  m_pos += m_velocity * m_speed * deltaTime;

  auto fric = Math::pow(m_friction, deltaTime);
  m_speed *= fric;

  lifeTime -= deltaTime;

  if (lifeTime <= 0) {
    kill();
  }

  // Collision
  if (b_tag == ProjectileTag::PROJECTILE_HERO) {
    for (auto mob : *g_enemies) {
      if (is_colliding(mob)) {
        mob->hit(-3, this);
        g_particle_system->grab_example(mob->get_pos() + vec2f(20, 25),
                                        m_angle);

        set_enable(false);
      }
    }
  }

  if (b_tag == ProjectileTag::PROJECTILE_ENEMY) {
    if (is_colliding(g_hero)) {
      l_hero->hit(-10, this);

      set_enable(false);
    }
  }
}

void Projectile::update(double deltaTime) {
  Entity::update(deltaTime);
}

void Projectile::draw() {
  Entity::draw();
}
