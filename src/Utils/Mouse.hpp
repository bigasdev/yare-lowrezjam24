#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Common.hpp"
#include "SDL.h"
namespace Mouse
{

  bool is_at_area(Area pArea, int width, int height);
  Area get_mouse_area(int width, int height);
  vec2f get_mouse_pos();
  float get_mouse_angle(vec2f pos);

  class MouseCursor
  {
    SDL_Rect rect;
    SDL_Rect point;

  public:
    MouseCursor(SDL_Rect rect = {0, 0, 16, 16}, SDL_Rect point = {0, 0, 1, 1})
    {
      // SDL_ShowCursor(SDL_DISABLE);
      this->rect = rect;
      this->point = point;
    }
    void disable_cursor() { SDL_ShowCursor(true); }
    void update()
    {
      vec2f mousePos = get_mouse_pos();
      rect.x = mousePos.x;
      rect.y = mousePos.y;
      point.x = mousePos.x;
      point.y = mousePos.y;
    }
  };
}; // namespace Mouse

#endif
