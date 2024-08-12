#pragma once
#ifndef WORM_HPP
#define WORM_HPP

#include "Boss.hpp"

#define WORM_HEALTH 100

class Worm : public Boss {
public:
  Worm();
  Worm(Resources *_resources, float _scale) : Boss(_resources, _scale) {}
  ~Worm();

  void walking_state(double deltaTime) override;
  void hit_state(double deltaTime) override;
  void invicible_state(double deltaTime) override;
  void rage_state(double deltaTime) override;

  void init() override;
  void fixed_update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;

  void animation_manager();

private:
};

#endif
