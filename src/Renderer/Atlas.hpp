#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <memory>
#include "../Utils/Common.hpp"

struct AtlasPoint {
  int xpu, ypu;
  int x, y;
};

class Entity;
class Camera;

class Atlas {
public:
  Atlas(SDL_Renderer *renderer, float* _scale);
  ~Atlas();

  void draw_texture(SDL_Texture *texture, vec2f scale, vec2f pos,
                    bool flip = false, int size = 1, bool ignore_scale = false);
  void draw_entity(Entity *entity, Camera *camera);
  void draw_unique_entity(std::unique_ptr<Entity> entity, Camera *camera);
  void draw_text(vec2f pos, const char *p_text, TTF_Font *font,
                 SDL_Color textColor, float size = 1, int width = 128);
  void draw_from_sheet(Entity *entity, Camera *camera);
  void draw_texture_from_sheet(SDL_Texture *texture, vec2f pos,
                               AtlasPoint point, Camera *camera, int scale = 1,
                               bool flip = false, bool ignore_scale = false);

  // getters
  SDL_Renderer *get_renderer();
  float get_game_scale();

  // void draw_pixel(Uint16 p_x, Uint16 p_y, Uint8 r, Uint8 g, Uint8 b, Uint8
  // a);
  void draw_pixel(float p_x, float p_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                  Camera *camera, int mode = 0, int scale = 1);
  void draw_line(vec2f start, vec2f end, vec3f color, int a, Camera *camera,
                 int mode = 0, int scale = 1);
  void draw_rect(vec2f pos, vec2f size, vec3f color, int a, Camera *camera, int mode = 0, int scale = 1);
  void draw_screen_filter(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
  SDL_Renderer *m_renderer_ptr;
  float* m_game_scale;
};
