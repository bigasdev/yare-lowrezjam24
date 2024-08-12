#include "Globals.hpp"

App *g_app;
Camera *g_camera;
Fort *g_fort;
CastleDBConverter *g_castledb;
ProjectileSystem *g_projectile_system;
ParticleSystem *g_particle_system;
InputManager *g_input_manager;
Atlas *g_atlas;
Resources *g_resources;

bool g_controller_connected;

GameState g_game_state = PLAYING;
HeroState g_hero_state = FARM;

vec2i g_grid = {175, 175}; 
