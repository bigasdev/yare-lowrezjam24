#pragma once

#ifndef PIXELDRAWER_HPP
#define PIXELDRAWER_HPP

#include "Common.hpp"

class Atlas;

namespace PixelDrawer {
void draw_area(vec2f pos, float radius, Atlas *atlas,
               vec3f color = {255, 0, 0});
void draw_rect(vec2f pos, vec2f size, Atlas *atlas, vec3f color = {255, 0, 0}, int a = 255, int mode = 0);
void draw_line(vec2f start, vec2f end, Atlas *atlas, vec3f color = {255, 0, 0});
void draw_circle(vec2f pos, float radius, Atlas *atlas,
                 vec3f color = {255, 0, 0});
} // namespace PixelDrawer

#endif
