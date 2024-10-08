#include "Globals.hpp"

bool is_paused = false;

App *g_app;
Camera *g_camera;
Fort *g_fort;
CastleDBConverter *g_castledb;
ProjectileSystem *g_projectile_system;
ParticleSystem *g_particle_system;
InputManager *g_input_manager;
Atlas *g_atlas;
Resources *g_resources;
SoundManager *g_sound_manager;
PlayerUI *g_player_ui;

bool g_controller_connected;

GameState g_game_state = PLAYING;
HeroState g_hero_state = FARM;
int g_hero_health = 100;

vec2i g_grid = {175, 175}; 
vec2f g_last_pos = {0,0};

bool has_planted_info = false;
bool has_merchant_info = false;
