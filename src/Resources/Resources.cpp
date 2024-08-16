#include "SDL_gpu.h"
#define CUTE_ASEPRITE_IMPLEMENTATION

#include "../Utils/cute_aseprite.h"
#include "AssetData.hpp"
#include "../Tools/Reader.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>

#include "Resources.hpp"

#include "../Utils/FDebug.hpp"
#include "SDL_opengl.h"

std::string mCurrentFolderResources = "";

namespace fs = std::filesystem;

Resources::Resources(SDL_Renderer *renderer)
{
  std::cout << "Instantied Resources!..." << std::endl;

  mRenderer = renderer;
  LoadAssets();
  LoadAseprites();
}

std::string get_aseprite_edited_time(const char *file)
{
  auto ftime = fs::last_write_time(file);
  auto ftime_since_epoch = ftime.time_since_epoch();

  auto now = std::chrono::system_clock::now();
  auto now_since_epoch = now.time_since_epoch();

  auto duration = ftime_since_epoch - now_since_epoch;
  auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      now + duration);

  auto cftime = std::chrono::system_clock::to_time_t(sctp);

  return std::to_string(cftime);
}

GPU_Image *CreateTextureFromRGBA(SDL_Renderer *renderer, const uint8_t *rgba,
                                 int width, int height)
{
  SDL_Surface *surface =
      SDL_CreateRGBSurfaceFrom((void *)rgba, width, height, 32, width * 4,
                               0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

  if (!surface)
  {
    std::cerr << "Failed to create SDL surface: " << SDL_GetError()
              << std::endl;
    return nullptr;
  }

  GPU_Image *texture = GPU_CopyImageFromSurface(surface);
  GPU_SetImageFilter(texture, GPU_FILTER_NEAREST);

  if (!texture)
  {
    std::cerr << "Failed to create SDL texture: " << SDL_GetError()
              << std::endl;
  }

  return texture;
}

void Resources::LoadAseprites()
{
  auto const &files = Reader::get_extension_files("res/", ".aseprite");
  m_aseprite_files.clear();

  if (m_aseprite_textures.size() > 0)
  {
    F_Debug::log("Detected changes!! Reloading...");
    for (auto const &file : files)
    {
      std::string fileName = file.substr(file.find_last_of("/") + 1);
      fileName = fileName.substr(0, fileName.find_last_of("."));

      GPU_Image **text = get_aseprite_texture(fileName.c_str());

      if (text != nullptr)
      {
        ase_t *ase = cute_aseprite_load_from_file(file.c_str(), NULL);

        ase_frame_t *frame = &ase->frames[0];
        const uint8_t *rgba =
            reinterpret_cast<const uint8_t *>(frame->ase->frames[0].pixels);
        GPU_Image *texture = CreateTextureFromRGBA(
            mRenderer, rgba, frame->ase->w, frame->ase->h);

        AsepriteHelper asepriteHelper;
        asepriteHelper.file = file;
        asepriteHelper.last_edited_time =
            get_aseprite_edited_time(file.c_str());
        m_aseprite_files.push_back(asepriteHelper);

        auto it = m_aseprite_textures.find(fileName.c_str());
        it->second = texture;

        F_Debug::log("Aseprite file reloaded: " + file);
      }
    }

    return;
  }

  for (auto const &file : files)
  {
    // first we get just the file name without the aseprite extension
    std::string fileName = file.substr(file.find_last_of("/") + 1);
    fileName = fileName.substr(0, fileName.find_last_of("."));

    F_Debug::log(file.c_str());

    ase_t *ase = cute_aseprite_load_from_file(file.c_str(), NULL);

    ase_frame_t *frame = &ase->frames[0];
    const uint8_t *rgba =
        reinterpret_cast<const uint8_t *>(frame->ase->frames[0].pixels);
    GPU_Image *texture =
        CreateTextureFromRGBA(mRenderer, rgba, frame->ase->w, frame->ase->h);

    AsepriteHelper asepriteHelper;
    asepriteHelper.file = file;
    asepriteHelper.last_edited_time = get_aseprite_edited_time(file.c_str());
    m_aseprite_files.push_back(asepriteHelper);

    m_aseprite_textures.insert(
        std::pair<const char *, GPU_Image *>(fileName.c_str(), texture));
  }
  F_Debug::log("Finished aseprite load!");
  F_Debug::log("------------");
  for (auto const &aseprite : m_aseprite_textures)
  {
    F_Debug::log_group("Aseprite", aseprite.first);
  }
}

void Resources::LoadFolder(std::string path)
{
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();

  auto const &files = Reader::read_file(path);
  int i = 0;
  int max = files.size();

  for (auto const &file : files)
  {
    // SaveTexture(file.c_str());

    // first we get just the file name without the png extension
    std::string fileName = file.substr(file.find_last_of("/") + 1);
    fileName = fileName.substr(0, fileName.find_last_of("."));

    CreateAssetData(file.c_str(), fileName.c_str(),
                    mCurrentFolderResources.c_str());

    i += 1;

    // current percentage:
    float percentage = (float)i / (float)max;
    // std::string percentageString = std::to_string(percentage * 100);
    // std::cout << "Loading: " << percentage * 100 << "%" << std::endl;
  }

  auto end = std::chrono::system_clock::now();

  // check the diff in milisseconds
  auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                  .count();
}

void Resources::LoadAssets()
{
  F_Debug::log("Loading assets...");
  auto const &folders = Reader::get_folders("res/sprites/");

  mFolders.push_back("sprites");

  for (auto const &folder : folders)
  {
    std::cout << "Loading the folder: " << folder << std::endl;

    // we get the string after the last "/"
    std::string folderName = folder.substr(folder.find_last_of("/") + 1);
    // std::cout << "Folder test name " << folderName << std::endl;

    mFolders.push_back(folderName);

    for (auto const &f : mFolders)
    {
      F_Debug::log_group("Folder", f.c_str());
    }

    mCurrentFolderResources = folderName;
    LoadFolder(folder + "/");
  }

  mCurrentFolderResources = "sprites";
  LoadFolder("res/sprites/");

  F_Debug::log("Assets loaded!");
}

GPU_Image *Resources::SaveTexture(const char *file)
{
  GPU_Image *texture;
  // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
  // "Loading %s", file);
  texture = GPU_LoadImage(file);
  if (texture)
  {
    // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
    // "Loaded %s", file);
    F_Debug::log_group("Loaded", file);
    // adding the texture to the cache
    mTextures.insert(std::pair<const char *, GPU_Image *>(file, texture));
  }
  else
  {
    F_Debug::error("Texture not found!");
  }
  return texture;
}
void Resources::CreateAssetData(const char *file, const char *name,
                                const char *folder)
{
  GPU_Image *texture;
  // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Trying
  // to create asset data :  %s, folder : %s", name, folder);
  texture = GPU_LoadImage(file);
  if (texture)
  {
    F_Debug::log_group("Asset data", file);
    // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
    // "Created asset data for: %s", file); adding the texture to the cache
    mAssets.insert(std::pair<std::string, AssetData *>(
        name, new AssetData(name, folder, texture)));
  }
  else
  {
    F_Debug::error("Asset " + std::string(name) + " not found!");
  }
}

std::vector<AssetData *> Resources::GetAssets(std::string folder)
{
  // we get all the assets of a folder
  std::vector<AssetData *> assets;
  for (auto const &asset : mAssets)
  {
    if (asset.second->GetFolder() == folder)
    {
      assets.push_back(asset.second);
    }
  }
  return assets;
}

AssetData *Resources::GetAsset(std::string name)
{
  // we get the asset by the name
  try
  {
    return mAssets.at(name);
  }
  catch (const std::out_of_range &e)
  {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Asset %s not found!", name.c_str());
    return nullptr;
  }
}

GPU_Image *Resources::GetTexture(const char *file, bool debug)
{
  auto const &cache = HandleMap(file);
  if (cache)
  {
    if (debug)
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "IMAGE %s on cache", file);
    return cache;
  }
  else
  {
    if (debug)
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Texture not found!");
    return nullptr;
  }
}

GPU_Image **Resources::get_aseprite_texture(const char *file)
{
  // we will get the texture from the map without a loop
  try
  {
    return &m_aseprite_textures.at(file);
  }
  catch (const std::out_of_range &e)
  {
    F_Debug::error("Texture " + std::string(file) + " not found!");
    return nullptr;
  }
}

GPU_Image *Resources::HandleMap(const char *file)
{
  // we will get the texture from the map without a loop
  try
  {
    std::string filePath = "res/sprites/";
    filePath += file;
    return mTextures.at(filePath);
  }
  catch (const std::out_of_range &e)
  {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   "Texture %s not found!", file);
    return nullptr;
  }
}

void Resources::aseprite_hot_reload()
{
  for (auto f : m_aseprite_files)
  {

    std::string new_edited_time = get_aseprite_edited_time(f.file.c_str());

    if (new_edited_time != f.last_edited_time)
    {
      F_Debug::log("Aseprite file changed: " + f.file);
      f.last_edited_time = new_edited_time;
      LoadAseprites();
    }
  }
}

std::vector<std::string> Resources::GetFolders() { return mFolders; }

std::map<std::string, GPU_Image *> Resources::GetTextures()
{
  return mTextures;
}

std::vector<std::string> Resources::GetTexturesName()
{
  // create a vector with the keys of the mTextures
  std::vector<std::string> keys;
  for (auto const &texture : mTextures)
  {
    keys.push_back(texture.first.substr(texture.first.find_last_of("/") + 1));
  }
  return keys;
}
