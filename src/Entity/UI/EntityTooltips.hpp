#pragma once
#ifndef ENTITYTOOLTIPS_HPP
#define ENTITYTOOLTIPS_HPP

#include "../../Utils/Common.hpp"

class SDL_Texture;

class EntityTooltips {
public:
  EntityTooltips() = default;
  ~EntityTooltips() = default;

  void draw(SDL_Texture* texture, vec2f pos);
};

#endif
