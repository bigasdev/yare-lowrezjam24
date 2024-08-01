#include "InputManager.hpp"
#include "SDL_keycode.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::bind_keyboard(SDL_KeyCode key, bool *value) {
  m_key_map[key] = value;
}

void InputManager::bind_mouse(bool *left, bool *right, bool *wheel) {
  left_click = left;
  right_click = right;
  wheel_click = wheel;
}

void InputManager::update(SDL_Event event) {
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (left_click != nullptr)
        *left_click = true;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
      if (right_click != nullptr)
        *right_click = true;
    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
      if (wheel_click != nullptr)
        *wheel_click = true;
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (left_click != nullptr)
        *left_click = false;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
      if (right_click != nullptr)
        *right_click = false;
    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
      if (wheel_click != nullptr)
        *wheel_click = false;
    }
    break;
  case SDL_KEYDOWN:
    if (m_key_map.find(event.key.keysym.sym) != m_key_map.end()) {
      *m_key_map[event.key.keysym.sym] = true;
    }
    break;
  case SDL_KEYUP:
    if (m_key_map.find(event.key.keysym.sym) != m_key_map.end()) {
      *m_key_map[event.key.keysym.sym] = false;
    }
    break;
  default:
    break;
  }
}
