#pragma once

#include "SDL.h"
#include "../Utils/Common.hpp"
#include "SDL_gpu.h"
#include <string>

// the class that will be used to store the data of the assets
// it will consist with the folder so we can reference it with the selected folder

class AssetData
{
public:
  AssetData(std::string name, std::string folder, GPU_Image *texture);
  ~AssetData();

  std::string GetName();
  void set_size(vec2f size);
  std::string GetFolder();
  GPU_Image *GetTexture();
  vec2f get_size();

private:
  std::string m_name;
  std::string m_folder;
  GPU_Image *m_texture;

  vec2f m_size;
};
