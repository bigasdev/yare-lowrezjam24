#pragma once
#ifndef HERO_HPP
#define HERO_HPP

#include "Entity.hpp"

struct HeroActions{
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool attack = false;
  bool interact = false;
  bool roll = false;
};

struct Inventory{
  int coins = 0;
  int carrots = 0;
  int potatos = 0;
  int pumpkins = 0;
};

class Hero : public Entity {
public:
  Hero();
  Hero(Resources* _resources, float _scale) : Entity(_resources, _scale) {}
  ~Hero();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  bool has_interact() { return actions.interact; }
  bool is_moving();

  Inventory* get_inventory() { return &inventory; }

  void animation_manager();
  
  HeroActions actions = {false,false,false,false,false,false,false};
private:
  Inventory inventory;
};

#endif
