#pragma once
#include <string>

class SDL_Texture;

struct AssetObject{
    SDL_Texture* texture;
    std::string layer;
    int x, y;

    AssetObject(SDL_Texture* texture, std::string layer, int x, int y){
        this->texture = texture;
        this->layer = layer;
        this->x = x;
        this->y = y;
    }
};
