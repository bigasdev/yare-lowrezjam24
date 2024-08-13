#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include "Entity.hpp"

class Item : public Entity {
public:
  Item();
  Item(Resources* _resources, float _scale) : Entity(_resources, _scale) {};
  ~Item();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

private:
  float float_speed = 0.5f;
  vec2f start_pos;
};

#endif
