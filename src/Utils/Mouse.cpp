#include "Mouse.hpp"

bool Mouse::is_at_area(Area pArea, int width, int height) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  int scaled_x = x * 64/width;
  int scaled_y = y * 64/height;
  // explanation of the magic numbers:
  // 4 are used to smoothen the edge-case detection
  // 8x8 is the width of the default cursor
  Area mouseArea = Area(scaled_x - 4, scaled_y - 4, 8, 8);
  return mouseArea.intersects(pArea);
}

Area Mouse::get_mouse_area(int width, int height) {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);

  int scaled_x = x * 64/width;
  int scaled_y = y * 64/height;

  return Area(scaled_x - 4, scaled_y - 4, 8, 8);
}

vec2f Mouse::get_mouse_pos() {
  int x = 0, y = 0;
  SDL_GetMouseState(&x, &y);
  return vec2f(x, y);
}

float Mouse::get_mouse_angle(vec2f pos) {
  vec2f mousePos = get_mouse_pos();
  return atan2(mousePos.y - pos.y, mousePos.x - pos.x);
}
