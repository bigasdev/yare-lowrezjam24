#include "InputManager.hpp"
#include "../Utils/FDebug.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"

InputManager::InputManager() {
  if (SDL_NumJoysticks() < 1) {
    F_Debug::error("No joysticks connected!\n");
  } else {
    // Load joystick
    auto controller = SDL_JoystickOpen(0);
    if (controller == NULL) {
      F_Debug::error("Unable to open game controller!");
    }
  }
}

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
  case SDL_JOYBUTTONUP:
    if (event.jbutton.button == 0) {
      if (left_click != nullptr)
        *left_click = false;
    } else if (event.jbutton.button == 1) {
      if (right_click != nullptr)
        *right_click = false;
    }
    break;
  case SDL_JOYBUTTONDOWN:
    F_Debug::log("button: %d" + std::to_string(event.jbutton.button));
    if (event.jbutton.button == 0) {
      if (left_click != nullptr)
        *left_click = true;
    } else if (event.jbutton.button == 1) {
      if (right_click != nullptr)
        *right_click = true;
    }
    break;
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
