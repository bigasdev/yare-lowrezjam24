#pragma once

#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include "Common.hpp"

class Atlas;

namespace Gizmos {
void draw_area(vec2f pos, float radius, Atlas *atlas,
               vec3f color = {255, 0, 0});
void draw_rect(vec2f pos, vec2f size, Atlas *atlas, vec3f color = {255, 0, 0});
void draw_line(vec2f start, vec2f end, Atlas *atlas, vec3f color = {255, 0, 0});
void draw_circle(vec2f pos, float radius, Atlas *atlas,
                 vec3f color = {255, 0, 0});
} // namespace Gizmos

#endif
