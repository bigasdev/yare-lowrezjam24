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

  CollisionBox2D coll;
  coll.offset = {0,0};
  coll.scale = {8,8};

  m_tileset_texture = g_resources->get_aseprite_texture("concept");
  for (int i = -size.x; i < size.x; i++) {
    for (int j = -size.y; j < size.y; j++) {
      tiles.push_back({i*8, j*8,coll, rnd(0, 9), 0});
    }
  }

  for(int i = 0; i < 12; i++){
    props.push_back({20 + i*8, 30, coll, 6, 1});
  }
}

void Room::draw() {
  for (auto& tile : tiles) {
    g_atlas->draw_texture_from_sheet(*m_tileset_texture, {static_cast<float>(tile.x),static_cast<float>(tile.y)}, {8,8,tile.tile,0}, g_camera);
  }
}

void Room::post_draw() {
  for (auto& prop : props) {
    g_atlas->draw_texture_from_sheet(*m_tileset_texture, {static_cast<float>(prop.x),static_cast<float>(prop.y)}, {8,8,0,prop.tile}, g_camera);
  }
}
