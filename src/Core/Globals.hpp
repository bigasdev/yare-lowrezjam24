#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "../Utils/Common.hpp"

enum GameState {
  PLAYING,
  PAUSED
};

enum HeroState{
  FARM,
  BATTLE,
  BATTLE_DEAD
};

class App;
class Camera;
class Fort;
class CastleDBConverter;
class ProjectileSystem;
class ParticleSystem;
class Atlas;
class Resources;
class InputManager;
class PlayerUI;

extern App *g_app;
extern Camera *g_camera;
extern Fort *g_fort;
extern CastleDBConverter *g_castledb;
extern ProjectileSystem *g_projectile_system;
extern ParticleSystem *g_particle_system;
extern InputManager *g_input_manager;
extern Atlas *g_atlas;
extern Resources *g_resources;
extern PlayerUI *g_player_ui;

extern bool g_controller_connected;
extern GameState g_game_state;
extern HeroState g_hero_state;

extern vec2i g_grid;

// UNIQUE STUFF
extern bool has_planted_info;
extern bool has_merchant_info;

#endif
