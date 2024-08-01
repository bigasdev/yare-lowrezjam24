#include "PixelDrawer.hpp"
#include "../Renderer/Atlas.hpp"

void PixelDrawer::draw_area(vec2f pos, float radius, Atlas *atlas,
                            vec3f color) {
  for (int i = 0; i < radius; ++i) {
    if (i == 0) {
      for (int j = 0; j < radius; ++j) {
        atlas->draw_pixel(pos.x + j, pos.y + i, color.x, color.y, color.z, 255,
                          nullptr);

        if (j == radius - 1) {
          for (int k = 0; k < radius; ++k) {
            atlas->draw_pixel(pos.x + radius, pos.y + k, color.x, color.y,
                              color.z, 255, nullptr);
          }
        }
      }
    }

    if (i == radius - 1) {
      for (int j = 0; j < radius; ++j) {
        atlas->draw_pixel(pos.x + j, pos.y + i, color.x, color.y, color.z, 255,
                          nullptr);
      }
    }

    atlas->draw_pixel(pos.x, pos.y + i, color.x, color.y, color.z, 255,
                      nullptr);
  }
}

void PixelDrawer::draw_rect(vec2f pos, vec2f size, Atlas *atlas, vec3f color, int a, int mode) {
  for (int i = 0; i < size.y; ++i) {
    for (int j = 0; j < size.x; ++j) {
      atlas->draw_pixel(pos.x + j, pos.y + i, color.x, color.y, color.z, a,
                        nullptr, mode);
    }
  }
}

void PixelDrawer::draw_line(vec2f start, vec2f end, Atlas *atlas, vec3f color) {
  float dx = end.x - start.x;
  float dy = end.y - start.y;
  float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  float x_inc = dx / steps;
  float y_inc = dy / steps;
  float x = start.x;
  float y = start.y;

  for (int i = 0; i < steps; ++i) {
    atlas->draw_pixel(x, y, color.x, color.y, color.z, 255, nullptr);
    x += x_inc;
    y += y_inc;
  }
}

void PixelDrawer::draw_circle(vec2f pos, float radius, Atlas *atlas,
                              vec3f color) {
  for (int i = 0; i < radius; ++i) {
    for (int j = 0; j < radius; ++j) {
      if (i * i + j * j <= radius * radius) {
        atlas->draw_pixel(pos.x + j, pos.y + i, color.x, color.y, color.z, 255,
                          nullptr);
      }
    }
  }
}
