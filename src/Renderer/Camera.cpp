#include "Camera.hpp"
#include "../Entity/Entity.hpp"

// private variables
bool is_shaking = false;
float shake_time = 0;
float shake_power = 0;
vec2f original_pos;

// control variables
float shake_timer = 0;

Camera::Camera(Entity *_target, vec2f *_screen_size, vec2i viewport) {
  m_target = _target;

  m_camera_size = _screen_size;
  m_viewport = viewport;

  // m_current_pos = m_target->get_pos();
  m_current_pos.x = m_camera_size->x / 2;
  m_current_pos.y = m_camera_size->y / 2;
}

void Camera::move(double deltaTime) {
  if (m_target == nullptr)
    return;

  // if (!target->isMoving())return;

  m_ref_pos = m_target->get_pos() + m_target->get_collision_box(1).scale;
  m_ref_pos.y -= 32;
  m_ref_pos.x -= 32;

  float x = m_ref_pos.x - m_current_pos.x;
  float y = m_ref_pos.y - m_current_pos.y;

  // std::cout << "Quick test: " << refPos.x << " " << refPos.y << "Camera : "
  // << x << " " << y << std::endl;

  // currentPos.x = refPos.x - (cameraSize.x / 2);
  // currentPos.y = refPos.y - (cameraSize.y / 2);

  m_current_pos.x =
      (1 - m_smooth_speed) * m_current_pos.x + m_smooth_speed * m_ref_pos.x;
  m_current_pos.y =
      (1 - m_smooth_speed) * m_current_pos.y + m_smooth_speed * m_ref_pos.y;

  /*
  currentPos.x += (x + smoothSpeed)-cameraSize.x/2;
  currentPos.y += (y + smoothSpeed)-cameraSize.y/2;*/

  // std::cout << "Current position of the camera : " << currentPos.x << "" <<
  // currentPos.y << std::endl;
}

void Camera::update(double deltaTime) {
  if (is_shaking) {
    shake_timer += deltaTime;

    m_ref_pos = m_target->get_pos() + m_target->get_collision_box(1).scale;
    m_ref_pos.y -= 32;
    m_ref_pos.x -= 32;

    m_current_pos.x = m_current_pos.x +
                      m_ref_pos.x * rnd(-shake_power, shake_power) * deltaTime;
    m_current_pos.y = m_current_pos.y +
                      m_ref_pos.y * rnd(-shake_power, shake_power) * deltaTime;

    F_Debug::log("Shake timer: " + std::to_string(shake_timer) +
                 " shake power: " + std::to_string(shake_power));
    F_Debug::log("Position: " + std::to_string(m_current_pos.x) + " " +
                 std::to_string(m_current_pos.y));

    if (shake_timer >= shake_time) {
      is_shaking = false;
      shake_timer = 0;
      m_current_pos = original_pos;
    }
  }
}

void Camera::update_camera_size(vec2f size) {}

bool Camera::is_on_screen(vec2f pos, float padding) {
  bool left = pos.x + padding < m_current_pos.x + (m_viewport.x);
  bool right = m_current_pos.x - (m_viewport.x) < pos.x + padding;
  bool top = pos.y + padding < m_current_pos.y + (m_viewport.y);
  bool bottom = m_current_pos.y - (m_viewport.y) < pos.y + padding;

  return left && right && top && bottom;
}

void Camera::set_entity(Entity *_target) {
  m_target = _target;
  m_ref_pos = m_target->get_pos();
  m_ref_pos.x -= m_camera_size->x / 2;
  m_ref_pos.y -= m_camera_size->y / 2;

  m_current_pos = m_ref_pos;
}

void Camera::set_pos(vec2f pos) { m_current_pos = pos; }

vec2f Camera::get_pos() { return m_current_pos; }

void Camera::set_shake(float power, float time) {
  if (is_shaking)
    return;

  is_shaking = true;
  original_pos = m_current_pos;

  shake_power = power;
  shake_time = time;
}
