#include "InputManager.hpp"
#include "../Core/Globals.hpp"
#include "../Utils/FDebug.hpp"
#include "SDL_events.h"
#include "SDL_joystick.h"
#include "SDL_keycode.h"

void connect_controller() {
  if (SDL_NumJoysticks() < 1) {
    F_Debug::error("No joysticks connected!\n");
  } else {
    // Load joystick
    auto controller = SDL_JoystickOpen(0);
    g_controller_connected = true;
    if (controller == NULL) {
      F_Debug::error("Unable to open game controller!");
    }
  }
}

InputManager::InputManager() { connect_controller(); }

InputManager::~InputManager() {}

void InputManager::bind_keyboard(SDL_KeyCode key, bool *value) {
  m_key_map[key] = value;
}

void InputManager::bind_joy(JoyInput key, bool *value) {
  m_joy_map[key] = value;
}

void InputManager::bind_mouse(bool *left, bool *right, bool *wheel) {
  left_click = left;
  right_click = right;
  wheel_click = wheel;
}

void InputManager::update(SDL_Event event) {
  switch (event.type) {
  case SDL_JOYDEVICEREMOVED:
    F_Debug::log("Controller Removed");
    g_controller_connected = false;
    break;
  case SDL_JOYDEVICEADDED:
    F_Debug::log("Controller Added");
    connect_controller();
    break;
  case SDL_JOYBUTTONDOWN:
    F_Debug::log(std::to_string(static_cast<JoyInput>(event.jbutton.button)));
    if (m_joy_map.find(static_cast<JoyInput>(event.jbutton.button)) !=
        m_joy_map.end()) {
      *m_joy_map[static_cast<JoyInput>(event.jbutton.button)] = true;
    }
    break;
  case SDL_JOYBUTTONUP:
    if (m_joy_map.find(static_cast<JoyInput>(event.jbutton.button)) !=
        m_joy_map.end()) {
      *m_joy_map[static_cast<JoyInput>(event.jbutton.button)] = false;
    }
    break;
  case SDL_JOYSTICK_AXIS_MAX:
    break;
  case SDL_JOYAXISMOTION:
    switch (event.jaxis.axis) {
    case 0:
      //Left X Axis
      if (event.jaxis.value < -8000) {
        raw_axis.x = -1;
      } else if (event.jaxis.value > 8000) {
        raw_axis.x = 1;
      } else {
        raw_axis.x = 0;
      }
      break;
    case 1:
      //Left Y axis
      if (event.jaxis.value < -8000) {
        raw_axis.y = -1;
      } else if (event.jaxis.value > 8000) {
        raw_axis.y = 1;
      } else {
        raw_axis.y = 0;
      }
      break;
    case 2:
      //Right x axis
      if (event.jaxis.value < -8000) {
        right_axis.x = -1;
      } else if (event.jaxis.value > 8000) {
        right_axis.x = 1;
      } else {
        right_axis.x = 0;
      }
      break;
    case 3:
      //Right y axis
      if (event.jaxis.value < -8000) {
        right_axis.y = -1;
      } else if (event.jaxis.value > 8000) {
        right_axis.y = 1;
      } else {
        right_axis.y = 0;
      }
      break;
    case 4:
      //LT
      if (event.jaxis.value > 8000) {
        if (m_joy_map.find(static_cast<JoyInput>(10)) !=
            m_joy_map.end()) {
          *m_joy_map[static_cast<JoyInput>(10)] = true;
        }
      } else {
        if (m_joy_map.find(static_cast<JoyInput>(10)) !=
            m_joy_map.end()) {
          *m_joy_map[static_cast<JoyInput>(10)] = false;
        }
      }
      break;
    case 5:
      //RT
      if (event.jaxis.value > 8000) {
        if (m_joy_map.find(static_cast<JoyInput>(11)) !=
            m_joy_map.end()) {
          *m_joy_map[static_cast<JoyInput>(11)] = true;
        }
      } else {
        if (m_joy_map.find(static_cast<JoyInput>(11)) !=
            m_joy_map.end()) {
          *m_joy_map[static_cast<JoyInput>(11)] = false;
        }
      }
      break;
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
    if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) {
      raw_axis.x = 1;
    }
    if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT) {
      raw_axis.x = -1;
    }
    if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
      raw_axis.y = -1;
    }
    if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
      raw_axis.y = 1;
    }
    break;
  case SDL_KEYUP:
    if (m_key_map.find(event.key.keysym.sym) != m_key_map.end()) {
      *m_key_map[event.key.keysym.sym] = false;
    }
    if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) {
      if (raw_axis.x != -1)
        raw_axis.x = 0;
    }
    if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT) {
      if (raw_axis.x != 1)
        raw_axis.x = 0;
    }
    if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
      if (raw_axis.y != 1)
        raw_axis.y = 0;
    }
    if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
      if (raw_axis.y != -1)
        raw_axis.y = 0;
    }
    break;
  default:
    break;
  }
}
