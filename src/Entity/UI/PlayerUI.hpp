#pragma once 
#ifndef PLAYERUI_HPP
#define PLAYERUI_HPP

class PlayerUI{
public: 
  PlayerUI();
  ~PlayerUI();

  void update(double deltaTime);
  void draw();
};

#endif
