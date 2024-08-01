#pragma once 

#include "Object.hpp"

class SDL_Texture;

class ImageObject : public Object
{
public:
    ImageObject(Area object_area = {0,0,50,50}, SDL_Texture* texture = nullptr, ObjectType type = IMAGE, int modifier = NILL);
    ~ImageObject();

    void set_texture(SDL_Texture *texture);
    SDL_Texture* get_texture();

private:
    SDL_Texture *m_texture;
};
