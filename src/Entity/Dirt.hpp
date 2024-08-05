#pragma once

#include "Entity.hpp"

class Dirt : public Entity {
public:
  Dirt();
  Dirt(Resources* _resources, float _scale) : Entity(_resources, _scale) {}
  ~Dirt();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  void animation_manager();
};
