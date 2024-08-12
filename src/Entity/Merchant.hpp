#pragma once
#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Entity.hpp"

#define SHUFFLE_TICKS 5
#define SHUFFLE_CD 0.25

class Merchant : public Entity {
public:
  Merchant();
  Merchant(Resources *_resources, float _scale) : Entity(_resources, _scale) {}
  ~Merchant();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  void animation_manager();
private:
  bool interact_range = false;
  bool shuffling_state = false;

  int shuffled_amt = 0;

  int shuffle_ticks = 0;
};

#endif

