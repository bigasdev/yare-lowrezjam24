#pragma once
#include <string>

class GPU_Image;

struct AssetObject
{
  GPU_Image *texture;
  std::string layer;
  int x, y;

  AssetObject(GPU_Image *texture, std::string layer, int x, int y)
  {
    this->texture = texture;
    this->layer = layer;
    this->x = x;
    this->y = y;
  }
};
