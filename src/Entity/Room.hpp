#pragma once
#ifndef ROOM_HPP
#define ROOM_HPP

#include "../Utils/Common.hpp"
#include <vector>
#include "SDL.h"

#define BATTLE_TIME 30

class GPU_Image;

struct Tile
{
  int x;
  int y;
  CollisionBox2D collision;
  int tile;
  int flags;
};

class Room
{
public:
  Room();
  Room(vec2i _pos, vec2i _size);
  ~Room();

  void update(double deltaTime);

  void draw();
  void post_draw();

private:
  vec2i pos;
  vec2i size;
  GPU_Image **m_tileset_texture;

  std::vector<Tile> tiles;
  std::vector<Tile> props;

  float battle_timer = 0;
};

#endif
