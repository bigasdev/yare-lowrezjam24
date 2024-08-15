#include "Room.hpp"
#include "../Core/App.hpp"
#include "../Core/Fort.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Resources/Resources.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Gizmos.hpp"
#include "Enemy.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"

Cooldown *m_room_cd = nullptr;

Room::Room() {}

Room::Room(vec2i _pos, vec2i _size) {
  pos = _pos;
  size = _size;

  m_room_cd = new Cooldown();

  CollisionBox2D coll;
  coll.offset = {0, 0};
  coll.scale = {8, 8};

  m_tileset_texture = g_resources->get_aseprite_texture("concept");
  for (int i = -size.x; i < size.x; i++) {
    for (int j = -size.y; j < size.y; j++) {
      tiles.push_back({i * 8, j * 8, coll, rnd(0, 9), 0});
    }
  }

  for (int i = 350; i < 900; i += 8) {
    for (int j = 350; j < 900; j += 8) {
      coll.scale = {8, 8};
      tiles.push_back({i, j, coll, 10, 0});
    }
  }

  for (int i = 0; i < 12; i++) {
    coll.scale = {12, 12};
    props.push_back({-40 + i * 8, 30, coll, 6, 1});
  }

  for (int i = -30; i < 175; i += 8) {
    coll.scale = {8, 8};
    props.push_back({-40, i, coll, 1, -1});
  }
  for (int i = -30; i < 175; i += 8) {
    coll.scale = {8, 8};
    props.push_back({190, i, coll, 1, -1});
  }
  for (int i = -100; i < 175; i += 8) {
    coll.scale = {8, 8};
    props.push_back({i, 175, coll, 1, -1});
  }
  for (int i = -100; i < 175; i += 8) {
    coll.scale = {8, 8};
    props.push_back({i, -30, coll, 1, -1});
  }

  // battle arena
  for (int i = 350; i < 900; i += 8) {
    coll.scale = {8, 8};
    props.push_back({i, 350, coll, 1, -1});
  }
  for (int i = 350; i < 900; i += 8) {
    coll.scale = {8, 8};
    props.push_back({i, 900, coll, 1, -1});
  }
  for (int i = 350; i < 900; i += 8) {
    coll.scale = {8, 8};
    props.push_back({350, i, coll, 1, -1});
  }
  for (int i = 350; i < 900; i += 8) {
    coll.scale = {8, 8};
    props.push_back({900, i, coll, 1, -1});
  }

  g_collider_tiles = &props;
}

void Room::update(double deltaTime) {
  m_room_cd->update(deltaTime);

  if (g_hero_state == HeroState::BATTLE) {
    battle_timer += deltaTime;
    if (!m_room_cd->has_state("spawn")) {
      for (int i = 0; i < 2; i++) {
        auto e = g_fort->recruit<Enemy>(g_resources, g_atlas->get_game_scale());
        e->set_pos(g_hero->get_pos().x + rnd(-90,90), g_hero->get_pos().y + rnd(-90,90));
        e->m_tag = Tag::ENEMY;
        e->init();
      }
      m_room_cd->set_state("spawn", 5.f, [&]() {});
    }

    if (battle_timer > 30.f) {
      battle_timer = 0;
      g_hero_state = HeroState::FARM;
      g_hero->set_pos(g_last_pos.x, g_last_pos.y);
    }
  }
}

void Room::draw() {
  for (auto &tile : tiles) {
    g_atlas->draw_texture_from_sheet(
        *m_tileset_texture,
        {static_cast<float>(tile.x), static_cast<float>(tile.y)},
        {8, 8, tile.tile, 0}, g_camera);
  }
#if F_ENABLE_DEBUG
  for (auto &prop : props) {
    Gizmos::draw_rect({static_cast<float>(prop.x), static_cast<float>(prop.y)},
                      prop.collision.scale, g_atlas, {255, 0, 0}, 100,
                      g_camera);
  }
#endif
  for (auto &prop : props) {
    if (prop.flags == -1)
      continue;
    g_atlas->draw_texture_from_sheet(
        *m_tileset_texture,
        {static_cast<float>(prop.x), static_cast<float>(prop.y)},
        {8, 8, 0, prop.tile}, g_camera);
  }
}

void Room::post_draw() {}
