#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include "Entity.hpp"

enum ItemType{
  STR,
  DEF,
  SPD,
  COIN
};

class Item : public Entity {
public:
  Item();
  Item(Resources* _resources, float _scale) : Entity(_resources, _scale) {};
  ~Item();

  void init() override;
  void set_coin();
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  void set_type(ItemType _type) { type = _type; }

private:
  float float_speed = 0.5f;
  vec2f start_pos;

  ItemType type = ItemType::STR;
};

#endif
