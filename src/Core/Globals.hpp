#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

class App;
class Camera;
class Fort;
class CastleDBConverter;
class ProjectileSystem;
class ParticleSystem;
class Atlas;
class Resources;

extern App *g_app;
extern Camera *g_camera;
extern Fort *g_fort;
extern CastleDBConverter *g_castledb;
extern ProjectileSystem *g_projectile_system;
extern ParticleSystem *g_particle_system;
extern Atlas *g_atlas;
extern Resources *g_resources;

extern int g_grid;

#endif
