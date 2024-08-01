#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Common.hpp"
#include "FDebug.hpp"
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "../Resources/Resources.hpp"

#include <functional>

struct Sprite {
  SDL_Texture **texture;

  int xpu, ypu;
  int x, y;

  bool facing_right = true;

  int sprite_scale_multiplier = 1;

  void* pixels;
  int pitch;
};

// this script will handle all the functionality that a sprite needs
class SpriteAnimation {
public:
  SpriteAnimation();

  SpriteAnimation(std::string name, vec2f pos, int frame_count,
                  double frame_timer, Sprite *sprite);

  void add_callback(std::function<void()> callback);
  void start();
  std::string get_name() const;

  void update(double deltaTime);

private:
  std::string name = "default";
  int current_frame;
  int frameCount;

  Sprite *m_sprite;

  double frame_timer = 0.1;
  double m_frame_time;
  int starting_x;
  int starting_y;

  std::function<void()> m_on_finish;
};
#endif
