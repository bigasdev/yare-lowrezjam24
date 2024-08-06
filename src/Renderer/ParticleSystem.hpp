#ifndef _PARTICLE_SYSTEM_HPP_
#define _PARTICLE_SYSTEM_HPP_

#pragma once

#include <math.h>
#include <vector>
#include "../Utils/Common.hpp"

class Atlas;
class Camera;

#include "SDL.h"

struct Particle {
  vec2f position;
  vec2f speed;
  float life_time = 1.5f;
  float opacity_decrease = .0f;
  int size = 3;
  int mode = 1;
  SDL_Color color = {255, 255, 255, 255};

  float friction = 0.0f;
  vec2f gravity = {0, 0};

  bool alive = true;
  bool fixed = false;

  float dx;
  float dy;

  void move_away_from_src(vec2f point, float speed) {
    float a = 0;
    if (point.x > 0)
      a = atan2(point.y - position.y, point.x - position.x);
    else
      a = atan2(point.y - position.y, point.x + position.x);
    dx = -cos(a) * speed;
    dy = -sin(a) * speed;
  }

  void move_to(vec2f point, float speed) {
    float x = position.x + point.x;
    float y = position.y + point.y;

    float a = x - position.x;
    float b = y - position.y;

    dx = a * speed;
    dy = b * speed;
  }
};

// System that will be used to create and manage particles
// right now it will work with creating a class for each kind of particles/
// TODO: make it ecs based
class ParticleSystem {
public:
  ParticleSystem(Atlas *atlas, Camera *camera, int max_particles);
  ~ParticleSystem();

  void update(double delta_time);
  void draw();

  void dots_explosion_example();
  void grab_example(vec2f pos, float angle);
  void walk_dust(vec2f pos);
  void snow_dust(vec2f pos);
  void plant_carrot(vec2f pos);
  void add_particle(Particle particle);

private:
  Atlas *m_atlas_ptr;
  Camera *m_camera_ptr;

  int m_max_particles;
  int m_current_particles;

  bool is_deleting_particle = false;

  std::vector<Particle> m_particles_vector;
};

#endif
