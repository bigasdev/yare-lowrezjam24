#include "EntityTooltips.hpp"
#include "../../Renderer/Atlas.hpp"
#include "../../Core/Globals.hpp"

void EntityTooltips::draw(SDL_Texture* texture, vec2f pos) {
  if(g_controller_connected){
    g_atlas->draw_texture_from_sheet(texture, pos, {8,8,0,1}, g_camera);
  }else{
    g_atlas->draw_texture_from_sheet(texture, pos, {16,16,3,1}, g_camera);
  }
}
