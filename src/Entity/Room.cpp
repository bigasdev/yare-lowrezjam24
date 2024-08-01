#include "Room.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Resources/Resources.hpp"
#include "EntityParty.hpp"

Room::Room() {}

Room::Room(vec2i _pos, vec2i _size) {
  pos = _pos;
  size = _size;

  m_tileset_texture = g_resources->get_aseprite_texture("character_atlas");
}

void Room::draw() {
  for (int i = -size.x; i < size.x; i++) {
    for (int j = -size.y; j < size.y; j++) {
      g_atlas->draw_texture_from_sheet(*m_tileset_texture,
                                       {pos.x + (i * (16 * g_camera->s_scale)),
                                        pos.y - (j * (16 * g_camera->s_scale))},
                                       {16, 16, 0, 1}, g_camera, 1, false);
    }
  }
}
