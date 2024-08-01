#pragma once

#include "SDL.h"
#include "../Utils/Common.hpp"
#include <string>

//the class that will be used to store the data of the assets
//it will consist with the folder so we can reference it with the selected folder

class AssetData{
public:
    AssetData(std::string name, std::string folder, SDL_Texture* texture);
    ~AssetData();

    std::string GetName();
    void set_size(vec2f size);
    std::string GetFolder();
    SDL_Texture* GetTexture();
    vec2f get_size();
    
private:
    std::string m_name;
    std::string m_folder;
    SDL_Texture* m_texture;

    vec2f m_size;
};  
