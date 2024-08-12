#pragma once 
#include "SDL_render.h"
#ifndef PLAYERUI_HPP
#define PLAYERUI_HPP

#include <string.h>
#include <iostream>

#define DIALOGUE_TIME 10 
#define TYPE_SPEED 0.05

class PlayerUI{
public: 
  PlayerUI();
  ~PlayerUI();

  void update(double deltaTime);
  void draw();
  void set_dialogue(std::string p_dialogue);
private:
  bool has_dialogue = false;
  std::string dialogue = "a";
  std::string new_dialogue;

  SDL_Texture** dialogue_texture;

  float dialogue_timer = 0;
  float type_timer = 0;
};

#endif
