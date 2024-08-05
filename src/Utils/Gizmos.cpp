#include "Gizmos.hpp"
#include "../Renderer/Atlas.hpp"

void Gizmos::draw_area(vec2f pos, float radius, Atlas *atlas, vec3f color) {
#if F_ENABLE_DEBUG
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
#endif
}

void Gizmos::draw_rect(vec2f pos, vec2f size, Atlas *atlas, vec3f color, int a, Camera* camera) {
#if F_ENABLE_DEBUG
  atlas->draw_rect(pos, size, color, a, camera, 2);
#endif
}

void Gizmos::draw_line(vec2f start, vec2f end, Atlas *atlas, vec3f color) {
#if F_ENABLE_DEBUG
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
#endif
}

void Gizmos::draw_circle(vec2f pos, float radius, Atlas *atlas, vec3f color) {
#if F_ENABLE_DEBUG
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    atlas->draw_pixel(pos.x + x, pos.y + y, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x + y, pos.y + x, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x - y, pos.y + x, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x - x, pos.y + y, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x - x, pos.y - y, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x - y, pos.y - x, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x + y, pos.y - x, color.x, color.y, color.z, 255,
                      nullptr);
    atlas->draw_pixel(pos.x + x, pos.y - y, color.x, color.y, color.z, 255,
                      nullptr);

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    }

    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
#endif
}
