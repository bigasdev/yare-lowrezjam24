#include "Sprite.hpp"

SpriteAnimation::SpriteAnimation() { this->name = "default"; }

SpriteAnimation::SpriteAnimation(std::string name, vec2f pos, int frame_count,
                                 double _frame_timer, Sprite *sprite) {
  this->name = name;
  current_frame = 0;
  frameCount = frame_count;
  m_sprite = sprite;
  starting_x = pos.x;
  starting_y = pos.y;
  frame_timer = _frame_timer;
  F_Debug::log(std::to_string(starting_x));
}

void SpriteAnimation::add_callback(std::function<void()> callback) {
  m_on_finish = callback;
}

void SpriteAnimation::start() {
  current_frame = 0;
  m_sprite->x = starting_x;
  m_sprite->y = starting_y;
}

std::string SpriteAnimation::get_name() const { return name; }

void SpriteAnimation::update(double deltaTime) {
  m_frame_time += 1 * deltaTime;

  // F_Debug::log_group("Frame Time", std::to_string(m_frame_time));
  // F_Debug::log_group("Frame Timer", std::to_string(frame_timer));
  F_Debug::log_group("Current Frame", std::to_string(current_frame));

  if (m_frame_time >= frame_timer) {
    m_frame_time = 0;
    current_frame += 1;
    m_sprite->x = starting_x + current_frame;
    // sheet_pos.x = starting_x + current_frame;
  }
  if (current_frame >= frameCount) {
    current_frame = 0;
    m_sprite->x = starting_x;
    // sheet_pos.x = starting_x;

    if (m_on_finish)
      m_on_finish();
  }
}
