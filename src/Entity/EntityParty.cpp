#include "EntityParty.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include "Item.hpp"
#include "Projectile.hpp"

std::vector<Entity *>* g_ALL;
Hero *g_hero;
std::vector<Entity *> g_tilesets;
std::vector<Entity *>* g_enemies;
std::vector<Item *> g_items;
std::vector<Projectile *> g_projectiles;

