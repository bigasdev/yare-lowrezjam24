#pragma once 
#ifndef BOSS_HPP
#define BOSS_HPP

#include "Entity.hpp"

enum BossState{
  WALKING,
  HIT_STATE,
  INVICIBLE_STATE,
  RAGE_STATE 
};

class Boss : public Entity {
public:
  Boss();
  Boss(Resources *_resources, float _scale) : Entity(_resources, _scale) {}
  ~Boss();

  void init() override;
  void fixed_update(double deltaTime) override;
  void update(double deltaTime) override;
  void draw() override;
  void post_update(double deltaTime) override;
  void change_state(BossState _state) { state = _state; }

  virtual void radial_shoot(int increase = 45);

  virtual void walking_state(double deltaTime);
  virtual void hit_state(double deltaTime);
  virtual void invicible_state(double deltaTime);
  virtual void rage_state(double deltaTime);


  void animation_manager();
protected:
  BossState state = WALKING;
};

#endif
