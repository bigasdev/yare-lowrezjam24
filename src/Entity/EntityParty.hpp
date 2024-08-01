#pragma once

#include <vector>
class Entity;
class Item;
class Projectile;
class Hero;

extern std::vector<Entity*>* g_ALL;
extern Hero* g_hero;
extern std::vector<Entity*> g_tilesets;
extern std::vector<Entity*>* g_enemies;
extern std::vector<Item*> g_items;
extern std::vector<Projectile*> g_projectiles;
