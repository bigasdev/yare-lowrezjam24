#pragma once
#include "../Utils/Common.hpp"
#include <SDL.h>

class Entity;

class Camera {
public:
  Camera(Entity *_target, vec2f* _screen_size, vec2i viewport);

  void move(double deltaTime);
  void update(double deltaTime);
  void update_camera_size(vec2f size);
  void set_entity(Entity *_target);
  void set_pos(vec2f pos);
  vec2f get_pos();

  bool is_on_screen(vec2f pos, float padding = 0);

  void set_shake(float power, float time);

  float s_scale = 1;
private:
  vec2f* m_camera_size;
  vec2i m_viewport;
  vec2f m_offset = vec2f(0, 0);
  float m_smooth_speed = .06f;

  // positions
  vec2f m_current_pos;
  vec2f m_ref_pos;

  Entity *m_target = nullptr;
};
