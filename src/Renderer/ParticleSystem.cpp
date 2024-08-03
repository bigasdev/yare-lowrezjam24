#include "ParticleSystem.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Utils/FDebug.hpp"
#include "../Utils/Math.hpp"
#include "../Core/Globals.hpp"

#include "../Utils/Common.hpp"
#include <cmath>

ParticleSystem::ParticleSystem(Atlas *atlas, Camera *camera,
                               int max_particles) {
  m_atlas_ptr = atlas;
  m_max_particles = max_particles;
  m_current_particles = 0;
  m_camera_ptr = camera;
}

ParticleSystem::~ParticleSystem() {}

void ParticleSystem::update(double delta_time) {
  // delete the particle memory if it's not alive
  if (is_deleting_particle) {
    for (auto it = m_particles_vector.begin();
         it != m_particles_vector.end();) {
      if (!it->alive) {
        it = m_particles_vector.erase(it);
      } else {
        ++it;
      }
    }
    is_deleting_particle = false;
  }

  for (auto &particle : m_particles_vector) {
    if (!particle.alive)
      continue;

    // Friction
    auto fric = Math::pow(particle.friction, delta_time);
    particle.dx *= fric;
    particle.dy *= fric;

    particle.position.x += particle.dx;
    particle.position.y -= particle.dy;
    particle.position.y += particle.gravity.y * delta_time;
    particle.position.x += particle.gravity.x * delta_time;

    particle.life_time -= delta_time;
    particle.color.a -= particle.opacity_decrease * delta_time;

    if (particle.life_time <= 0) {
      particle.alive = false;
      is_deleting_particle = true;
      // delete &particle;
    }
  }
}

void ParticleSystem::draw() {
  for (auto &particle : m_particles_vector) {
    if (!particle.alive)
      continue;

    if(particle.fixed){
      m_atlas_ptr->draw_pixel(particle.position.x, particle.position.y,
                              particle.color.r, particle.color.g,
                              particle.color.b, particle.color.a, g_camera, particle.mode,
                              particle.size);
      continue;
    }
    m_atlas_ptr->draw_pixel(particle.position.x, particle.position.y,
                            particle.color.r, particle.color.g,
                            particle.color.b, particle.color.a, m_camera_ptr, particle.mode,
                            particle.size);
  }
}

void ParticleSystem::dots_explosion_example() {
  for (int i = 0; i < 80; i++) {
    Particle particle;
    particle.color.a = rnd(20, 255);
    particle.opacity_decrease = rnd(0.5f, 3.5f);
    particle.position = {150, 150};
    particle.move_away_from_src({rnd(-3, 3), rnd(1, 7)}, rnd(0.4f, 1.f));
    particle.friction = rnd(0.8f, 0.9f);
    particle.gravity = {rnd(0.5f, 1.2f), rnd(0.5f, 1.2f)};
    particle.life_time = rnd(2, 5);

    add_particle(particle);
  }
}

void ParticleSystem::grab_example(vec2f pos, float angle) {
  for (int i = 0; i < 80; i++) {
    Particle particle;
    particle.color = {255, 255, 255, 255};
    particle.color.a = rnd(30, 195);
    particle.opacity_decrease = 0;
    particle.size = rnd(1, 2);
    particle.mode = 1;
    particle.position = {pos.x + rnd(-15.f, 15.f), pos.y};
    auto x = cos(-angle) * rnd(130, 250);
    auto y = sin(-angle) * rnd(130, 250);
    particle.move_to({x, y}, rnd(.01f, .03f));
    particle.friction = rnd(.8f, .9f);
    particle.gravity = {0, .1f};
    particle.life_time = rnd(41.2f, 44.2f);

    add_particle(particle);
  }
}

void ParticleSystem::walk_dust(vec2f pos) {
  for (int i = 0; i < 8; i++) {
    Particle particle;
    particle.color = {255, 255, 255, 255};
    particle.color.a = rnd(20, 255);
    particle.opacity_decrease = rnd(0.15f, .5f);
    particle.position = {pos.x + rnd(5, 15), pos.y + rnd(15, 25)};
    particle.move_away_from_src({15, 0}, rnd(0.1f, 0.3f));
    particle.friction = rnd(.8f, .9f);
    particle.gravity = {5, 0};
    particle.life_time = rnd(1.8f, 3.2f);

    add_particle(particle);
  }
}

void ParticleSystem::snow_dust(vec2f pos) {
  for (int i = 0; i < 18; i++) {
    Particle particle;
    particle.color = {255, 255, 255, 255};
    particle.size = rnd(1,2);
    particle.mode = 1;
    particle.fixed = true;
    particle.color.a = rnd(45, 125);
    particle.opacity_decrease = 0;
    particle.position = {pos.x + rnd(5, 35), pos.y + rnd(2.5f, 45.f)};
    particle.move_away_from_src({15, 0}, rnd(0.1f, 0.15f));
    particle.friction = rnd(.8f, .9f);
    particle.gravity = {rnd(.08f, .12f), rnd(.05f, .1f)};
    if(particle.size == 1)particle.gravity = {rnd(.2f, .35f), rnd(.15f, .25f)};
    particle.life_time = rnd(220.8f, 345.2f);

    add_particle(particle);
  }
}

void ParticleSystem::add_particle(Particle particle) {
  if (m_particles_vector.size() >= m_max_particles){
    m_particles_vector.erase(m_particles_vector.begin(), m_particles_vector.begin() +100);
  }

  m_particles_vector.push_back(particle);
}
