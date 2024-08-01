#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <map>
#include <vector>

class AssetData;

struct AsepriteHelper
{
  std::string file;
  std::string last_edited_time;
};

class Resources
{
public:
  Resources(SDL_Renderer *renderer);

  void LoadAseprites();
  void LoadFolder(std::string path);
  void LoadAssets();
  SDL_Texture *SaveTexture(const char *file);
  SDL_Texture *GetTexture(const char *file, bool debug);
  SDL_Texture **get_aseprite_texture(const char *file);
  SDL_Texture *HandleMap(const char *file);

  void aseprite_hot_reload();

  // asset data creation
  void CreateAssetData(const char *file, const char *name, const char *folder);
  std::vector<AssetData *> GetAssets(std::string folder);
  AssetData *GetAsset(std::string name);

  // getters
  std::vector<std::string> GetFolders();

  std::map<std::string, SDL_Texture *> GetTextures();
  std::vector<std::string> GetTexturesName();

private:
  std::map<std::string, SDL_Texture *> mTextures;
  std::map<std::string, AssetData *> mAssets;
  SDL_Renderer *mRenderer;

  // aseprite
  std::map<std::string, SDL_Texture *> m_aseprite_textures;
  std::vector<AsepriteHelper> m_aseprite_files;

  std::vector<std::string> mFolders;
};
