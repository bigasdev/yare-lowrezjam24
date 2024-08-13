#pragma once 
#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include "SDL_mixer.h"
#include <iostream>
#include <string>
#include <vector>

struct Sound {
  Mix_Chunk *chunk;
  std::string name;
};

class SoundManager {
public:
  SoundManager();
  ~SoundManager();

  void load_sound(const char *path, std::string name);
  void play_sound(std::string name);
  void play_music();
  void stop_music();
  void pause_music();
  void resume_music();
  void set_volume(int volume);
  void set_music_volume(int volume);

private:
  std::vector<Sound> m_sounds;
  Mix_Music *m_music;
  int m_volume;
  int m_music_volume;
};

#endif
