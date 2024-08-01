#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include "Entity.hpp"

class Item : public Entity {
public:
  Item();
  Item(Resources* _resources, float _scale);
  ~Item();

  void update(double deltaTime);

  void add_hero(Entity** _hero) { m_hero = *_hero; }

private:
  Entity* m_hero;

  float float_speed = 0.5f;
  vec2f start_pos;
};

#endif
