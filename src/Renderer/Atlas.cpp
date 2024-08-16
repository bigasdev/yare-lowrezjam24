#include "Atlas.hpp"
#include "../Entity/Entity.hpp"
#include "../Renderer/Camera.hpp"
#include "SDL_blendmode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "SDL_gpu.h"
#include <tuple>

Atlas::Atlas(SDL_Renderer *renderer, float *_scale) {
  std::cout << "Instantiated atlas!..." << std::endl;
  m_game_scale = _scale;
  m_renderer_ptr = renderer;
}

Atlas::~Atlas() {}

float Atlas::get_game_scale() { return *m_game_scale; }

// the simple draw function, its used to show a sprite in the screen
void Atlas::draw_texture(SDL_Texture *texture, vec2f scale, vec2f pos,
                         bool flip, int size, bool ignore_size) {

  SDL_Rect dst;
  if (!ignore_size)
    size = *m_game_scale * size;
  dst.x = (pos.x + (scale.x * size - scale.x * size) / 2);
  dst.y = (pos.y + (scale.y * size - scale.y * size) / 2);
  dst.w = scale.x * size;
  dst.h = scale.y * size;

  /*SDL_Rect dst;
  dst.w = scale.x*size;
  dst.h = scale.y*size;
  dst.x = xpos + (dst.w * size - dst.w * size * dst.x) / 2;
  dst.y = ypos + (dst.h * size - dst.h * size * dst.y) / 2;*/

  auto flip_state = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_RenderCopyEx(m_renderer_ptr, texture, NULL, &dst, 0, 0, flip_state);
}
void Atlas::draw_entity(Entity *p_entity, Camera *p_camera) {
  if (!p_entity->is_visible())
    return;

  SDL_Rect src;
  src.x = p_entity->get_current_frame().x;
  src.y = p_entity->get_current_frame().y;
  src.w = p_entity->get_current_frame().w * *m_game_scale;
  src.h = p_entity->get_current_frame().h * *m_game_scale;

  SDL_Rect dst;
  dst.x = (p_entity->get_pos().x +
           (p_entity->get_current_frame().w * *m_game_scale -
            p_entity->get_current_frame().w * *m_game_scale *
                p_entity->get_scale().x) /
               2) -
          p_camera->get_pos().x;
  dst.y = (p_entity->get_pos().y +
           (p_entity->get_current_frame().h * *m_game_scale -
            p_entity->get_current_frame().h * *m_game_scale *
                p_entity->get_scale().y) /
               2) -
          p_camera->get_pos().y;
  dst.w =
      p_entity->get_current_frame().w * p_entity->get_scale().x * *m_game_scale;
  dst.h =
      p_entity->get_current_frame().h * p_entity->get_scale().y * *m_game_scale;

  // std::cout << "checks src" << "x " << src.x << " y " << src.y << " w " <<
  // src.w << " h " << src.h << std::endl; std::cout << "checks" << "x " <<
  // dst.x << " y " << dst.y << " w " << dst.w << " h " << dst.h << std::endl;

  // std::cout << "just testing? " << p_entity->getTexture() << "renderer" <<
  // rendererptr << "size : " << dst.h << std::endl;

  SDL_RenderCopyEx(m_renderer_ptr, p_entity->get_texture(), &src, &dst,
                   p_entity->get_angle(), 0, SDL_FLIP_NONE);
}
void Atlas::draw_unique_entity(std::unique_ptr<Entity> p_entity,
                               Camera *p_camera) {
  if (!p_entity->is_visible())
    return;

  SDL_Rect src;
  src.x = p_entity->get_current_frame().x;
  src.y = p_entity->get_current_frame().y;
  src.w = p_entity->get_current_frame().w * *m_game_scale;
  src.h = p_entity->get_current_frame().h * *m_game_scale;

  SDL_Rect dst;
  dst.x = (p_entity->get_pos().x +
           (p_entity->get_current_frame().w * *m_game_scale -
            p_entity->get_current_frame().w * *m_game_scale *
                p_entity->get_scale().x) /
               2) -
          p_camera->get_pos().x;
  dst.y = (p_entity->get_pos().y +
           (p_entity->get_current_frame().h * *m_game_scale -
            p_entity->get_current_frame().h * *m_game_scale *
                p_entity->get_scale().y) /
               2) -
          p_camera->get_pos().y;
  dst.w =
      p_entity->get_current_frame().w * p_entity->get_scale().x * *m_game_scale;
  dst.h =
      p_entity->get_current_frame().h * p_entity->get_scale().y * *m_game_scale;

  // std::cout << "checks src" << "x " << src.x << " y " << src.y << " w " <<
  // src.w << " h " << src.h << std::endl; std::cout << "checks" << "x " <<
  // dst.x << " y " << dst.y << " w " << dst.w << " h " << dst.h << std::endl;

  // std::cout << "just testing? " << p_entity->getTexture() << "renderer" <<
  // rendererptr << "size : " << dst.h << std::endl;

  SDL_RenderCopyEx(m_renderer_ptr, p_entity->get_texture(), &src, &dst,
                   p_entity->get_angle(), 0, SDL_FLIP_NONE);
}

void Atlas::draw_text(vec2f pos, const char *p_text, TTF_Font *font,
                      SDL_Color textColor, float size, int width,
                      Camera *camera) {
  SDL_Surface *surfaceMessage =
      TTF_RenderText_Blended_Wrapped(font, p_text, textColor, width);
  SDL_Texture *message =
      SDL_CreateTextureFromSurface(m_renderer_ptr, surfaceMessage);

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surfaceMessage->w;
  src.h = surfaceMessage->h;

  SDL_Rect dst;
  dst.x = pos.x;
  dst.y = pos.y;
  if (camera != nullptr) {
    dst.x -= camera->get_pos().x;
    dst.y -= camera->get_pos().y;
  }
  dst.w = src.w * size;
  dst.h = src.h * size;

  SDL_FreeSurface(surfaceMessage);
  SDL_RenderCopyEx(m_renderer_ptr, message, &src, &dst, 0, 0, SDL_FLIP_NONE);
  SDL_DestroyTexture(message);
}

void Atlas::draw_from_sheet(Entity *entity, Camera *camera) {

  /*bool visible = entity->is_visible();
  if (!visible) {
    return;
  }*/

  if (entity->get_current_sprite()->texture == nullptr) {
    return;
  }

  Sprite curr_sprite = *entity->get_current_sprite();
  int game_scale = *m_game_scale;

  int scaled_x =
      curr_sprite.xpu * (game_scale + curr_sprite.sprite_scale_multiplier);
  int scaled_y =
      curr_sprite.ypu * (game_scale + curr_sprite.sprite_scale_multiplier);

  SDL_Rect src = {curr_sprite.x * curr_sprite.xpu,
                  curr_sprite.y * curr_sprite.ypu, curr_sprite.xpu,
                  curr_sprite.ypu};

  vec2f pos = entity->get_pos();
  vec2f cam_pos = camera->get_pos();

  SDL_Rect dst = {static_cast<int>(pos.x) - static_cast<int>(cam_pos.x),
                  static_cast<int>(pos.y) - static_cast<int>(cam_pos.y),
                  scaled_x, scaled_y};

  auto flip = !curr_sprite.facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  // SDL_SetTextureColorMod(*entity->get_current_sprite()->texture, 255, 0, 0);

  SDL_RenderCopyEx(m_renderer_ptr, *entity->get_current_sprite()->texture, &src,
                   &dst, entity->get_angle(), 0, flip);
  // SDL_SetTextureColorMod(*entity->get_current_sprite()->texture, 255, 255,
  // 255);
}
void Atlas::draw_texture_from_sheet(SDL_Texture *texture, vec2f pos,
                                    AtlasPoint point, Camera *camera, int scale,
                                    bool flip, bool ignore_scale) {

  int scaled_x = point.xpu * (*m_game_scale + scale);
  int scaled_y = point.ypu * (*m_game_scale + scale);

  if (ignore_scale) {
    scaled_x = point.xpu;
    scaled_y = point.ypu;
  }

  SDL_Rect src = {point.x * point.xpu, point.y * point.ypu, point.xpu,
                  point.ypu};
  SDL_Rect dst;
  if (camera != nullptr) {
    dst = {static_cast<int>(pos.x) - static_cast<int>(camera->get_pos().x),
           static_cast<int>(pos.y) - static_cast<int>(camera->get_pos().y),
           scaled_x, scaled_y};
  } else {
    dst = {static_cast<int>(pos.x), static_cast<int>(pos.y), scaled_x,
           scaled_y};
  }

  auto flip_state = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

  SDL_RenderCopyEx(m_renderer_ptr, texture, &src, &dst, 0, 0, flip_state);
}

SDL_Renderer *Atlas::get_renderer() { return m_renderer_ptr; }

void Atlas::draw_pixel(float p_x, float p_y, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                       Camera *camera, int mode, int scale) {
  SDL_SetRenderDrawColor(m_renderer_ptr, r, g, b, a);

  switch (mode) {
  case 0:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  case 1:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_ADD);
    break;
  case 2:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_BLEND);
    break;
  case 3:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MOD);
    break;
  case 4:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MUL);
    break;
  default:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  }

  if (camera != nullptr) {
    p_x -= camera->get_pos().x;
    p_y -= camera->get_pos().y;
  }
  for (int dx = 0; dx < scale; ++dx) {
    for (int dy = 0; dy < scale; ++dy) {
      SDL_RenderDrawPoint(m_renderer_ptr, p_x + dx, p_y + dy);
    }
  }
}

void Atlas::draw_line(vec2f start, vec2f end, vec3f color, int a,
                      Camera *camera, int mode, int scale) {
  SDL_SetRenderDrawColor(m_renderer_ptr, color.x, color.y, color.z, a);

  switch (mode) {
  case 0:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  case 1:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_ADD);
    break;
  case 2:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_BLEND);
    break;
  case 3:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MOD);
    break;
  case 4:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MUL);
    break;
  default:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  }

  if (camera != nullptr) {
    start.x -= camera->get_pos().x;
    start.y -= camera->get_pos().y;
    end.x -= camera->get_pos().x;
    end.y -= camera->get_pos().y;
  }

  SDL_RenderDrawLine(m_renderer_ptr, start.x, start.y, end.x, end.y);
}

void Atlas::draw_rect(vec2f pos, vec2f size, vec3f color, int a, Camera *camera,
                      int mode, int scale) {
  SDL_SetRenderDrawColor(m_renderer_ptr, color.x, color.y, color.z, a);

  switch (mode) {
  case 0:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  case 1:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_ADD);
    break;
  case 2:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_BLEND);
    break;
  case 3:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MOD);
    break;
  case 4:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_MUL);
    break;
  default:
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_NONE);
    break;
  }

  if (camera != nullptr) {
    pos.x -= camera->get_pos().x;
    pos.y -= camera->get_pos().y;
  }

  SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y),
                   static_cast<int>(size.x * scale),
                   static_cast<int>(size.y * scale)};
  SDL_RenderFillRect(m_renderer_ptr, &rect);
}

void Atlas::draw_screen_filter(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int mode) {
  SDL_SetRenderDrawColor(m_renderer_ptr, r, g, b, a);
  if (mode == 1) {
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_ADD);
  } else {
    SDL_SetRenderDrawBlendMode(m_renderer_ptr, SDL_BLENDMODE_BLEND);
  }
  SDL_RenderFillRect(m_renderer_ptr, NULL);
}
