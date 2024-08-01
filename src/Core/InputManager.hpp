#pragma once
#include "SDL_keycode.h"
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "SDL.h"
#include <map>

class InputManager{
public:
  InputManager();
  ~InputManager();

  void bind_keyboard(SDL_KeyCode key, bool* value);
  void bind_mouse(bool* left, bool* right, bool* wheel);
  void update(SDL_Event event);

private:
  std::map<SDL_Keycode, bool*> m_key_map;

  bool* left_click = nullptr;
  bool* right_click = nullptr;
  bool* wheel_click = nullptr;
};

#endif
