#pragma once
#ifndef DIRT_HPP
#define DIRT_HPP

#include "Entity.hpp"

#define PLANT_CD 15

class Dirt : public Entity {
public:
  Dirt();
  Dirt(Resources *_resources, float _scale) : Entity(_resources, _scale) {}
  ~Dirt();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  void animation_manager();

private:
  bool interact_range = false;
  bool has_plant = false;

  int plant_state = 0;
};
#endif
