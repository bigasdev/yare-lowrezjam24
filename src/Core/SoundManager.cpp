#include "SoundManager.hpp"
#include "../Utils/FDebug.hpp"

SoundManager::SoundManager() {
  load_sound("res/sounds/damage_sound.wav", "damage");
  load_sound("res/sounds/entering.wav", "entering");
  load_sound("res/sounds/merchant_finish.wav", "merchant_finish");
  load_sound("res/sounds/merchant_tick.wav", "merchant_tick");
  load_sound("res/sounds/pause.wav", "pause");
  load_sound("res/sounds/planting.wav", "planting");
  load_sound("res/sounds/shoot.wav", "shoot");
  load_sound("res/sounds/unpause.wav", "unpause");
  load_sound("res/sounds/victory.wav", "victory");
}

SoundManager::~SoundManager() {
  for (auto sound : m_sounds) {
    Mix_FreeChunk(sound.chunk);
  }
  Mix_FreeMusic(m_music);
  Mix_CloseAudio();
}

void SoundManager::load_sound(const char *path, std::string name) {
  Sound sound;
  sound.chunk = Mix_LoadWAV(path);
  if(sound.chunk == NULL){
    F_Debug::log("SoundManager::load_sound: failed to load sound " + name);
    return;
  }else{
    F_Debug::log("SoundManager::load_sound: loaded sound " + name);
  }
  sound.name = name;
  m_sounds.push_back(sound);
}

void SoundManager::play_sound(std::string name) {
  for (auto sound : m_sounds) {
    if (sound.name == name) {
      Mix_PlayChannel(-1, sound.chunk, 0);
      return;
    }
  }
  F_Debug::log("SoundManager::play_sound: sound not found");
}

void SoundManager::play_music() {
  Mix_PlayMusic(m_music, -1);
}

void SoundManager::stop_music() {
  Mix_HaltMusic();
}

void SoundManager::pause_music() {
  Mix_PauseMusic();
}

void SoundManager::resume_music() {
  Mix_ResumeMusic();
}

void SoundManager::set_volume(int volume) {
  m_volume = volume;
  Mix_Volume(-1, m_volume);
}

void SoundManager::set_music_volume(int volume) {
  m_music_volume = volume;
  Mix_VolumeMusic(m_music_volume);
}
