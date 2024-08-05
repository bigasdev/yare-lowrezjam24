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

  m_tileset_texture = g_resources->get_aseprite_texture("concept");
  for (int i = -size.x; i < size.x; i++) {
    for (int j = -size.y; j < size.y; j++) {
      tiles.push_back({i*8, j*8, rnd(0, 7), 0});
    }
  }
}

void Room::draw() {
  for (auto& tile : tiles) {
    g_atlas->draw_texture_from_sheet(*m_tileset_texture, {static_cast<float>(tile.x),static_cast<float>(tile.y)}, {8,8,tile.tile,0}, g_camera);
  }
}
