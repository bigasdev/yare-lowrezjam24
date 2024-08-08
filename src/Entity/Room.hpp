#pragma once 
#ifndef ROOM_HPP
#define ROOM_HPP

#include "../Utils/Common.hpp"
#include <vector>
#include "SDL.h"

struct Tile{
  int x;
  int y;
  CollisionBox2D collision;
  int tile;
  int flags;
};

class Room{
public:
  Room();
  Room(vec2i _pos, vec2i _size);
  ~Room();

  void draw();
  void post_draw();
private:
  vec2i pos;
  vec2i size;
  SDL_Texture** m_tileset_texture;

  std::vector<Tile> tiles;
  std::vector<Tile> props;
};

#endif
