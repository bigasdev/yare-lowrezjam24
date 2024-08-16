#include "ImageObject.hpp"
#include "SDL.h"
#include "SDL_image.h"

ImageObject::ImageObject(Area object_area, GPU_Image *texture, ObjectType type, int modifier) : Object(object_area, type, modifier)
{
  m_texture = texture;
}

ImageObject::~ImageObject()
{
}

void ImageObject::set_texture(GPU_Image *texture)
{
}

GPU_Image *ImageObject::get_texture()
{
  return m_texture;
}
