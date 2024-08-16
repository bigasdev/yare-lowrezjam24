#include "EntityTooltips.hpp"
#include "../../Renderer/Atlas.hpp"
#include "../../Core/Globals.hpp"

void EntityTooltips::draw(GPU_Image *texture, vec2f pos)
{
  if (g_controller_connected)
  {
    g_atlas->draw_texture_from_sheet(texture, pos, {8, 8, 22, 0}, g_camera);
  }
  else
  {
    g_atlas->draw_texture_from_sheet(texture, pos, {8, 8, 20, 0}, g_camera);
  }
}
