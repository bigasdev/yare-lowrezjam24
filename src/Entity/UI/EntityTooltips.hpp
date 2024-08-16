#pragma once
#ifndef ENTITYTOOLTIPS_HPP
#define ENTITYTOOLTIPS_HPP

#include "../../Utils/Common.hpp"

class GPU_Image;

class EntityTooltips
{
public:
  EntityTooltips() = default;
  ~EntityTooltips() = default;

  void draw(GPU_Image *texture, vec2f pos);
};

#endif
