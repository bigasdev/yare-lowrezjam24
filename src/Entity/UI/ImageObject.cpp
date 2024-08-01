#include "ImageObject.hpp"
#include "SDL.h"
#include "SDL_image.h"

ImageObject::ImageObject(Area object_area, SDL_Texture* texture, ObjectType type, int modifier) : Object(object_area, type, modifier)
{
    m_texture = texture;
}

ImageObject::~ImageObject()
{
}

void ImageObject::set_texture(SDL_Texture *texture)
{
}

SDL_Texture *ImageObject::get_texture()
{
    return m_texture;
}
