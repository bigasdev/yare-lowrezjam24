#include "AssetData.hpp"

AssetData::AssetData(std::string name, std::string folder, SDL_Texture *texture)
{
    m_name = name;
    m_folder = folder;
    m_texture = texture;
}

AssetData::~AssetData()
{

}

std::string AssetData::GetName()
{
    return m_name;
}

void AssetData::set_size(vec2f size)
{
    m_size = size;
}

std::string AssetData::GetFolder()
{
    return m_folder;
}

SDL_Texture *AssetData::GetTexture()
{
    return m_texture;
}

vec2f AssetData::get_size()
{
    return m_size;
}
