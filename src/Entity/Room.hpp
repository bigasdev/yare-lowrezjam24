#pragma once 
#ifndef ROOM_HPP
#define ROOM_HPP

#include "../Utils/Common.hpp"
#include "SDL.h"

class Room{
public:
  Room();
  Room(vec2i _pos, vec2i _size);
  ~Room();

  void draw();
private:
  vec2i pos;
  vec2i size;
  SDL_Texture** m_tileset_texture;
};

#endif
