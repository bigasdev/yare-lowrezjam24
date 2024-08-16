#pragma once

#include "Object.hpp"

class GPU_Image;

class ImageObject : public Object
{
public:
  ImageObject(Area object_area = {0, 0, 50, 50}, GPU_Image *texture = nullptr, ObjectType type = IMAGE, int modifier = NILL);
  ~ImageObject();

  void set_texture(GPU_Image *texture);
  GPU_Image *get_texture();

private:
  GPU_Image *m_texture;
};
