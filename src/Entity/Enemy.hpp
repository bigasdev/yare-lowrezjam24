#pragma once 
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
  Enemy();
  Enemy(Resources *_resources, float _scale) : Entity(_resources, _scale) {}
  ~Enemy();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void post_update(double deltaTime) override;
  void draw() override;
};

#endif
