#include "Item.hpp"
#include "../Core/Globals.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include "../Renderer/Camera.hpp"
#include "../Tools/Cooldown.hpp"

Item::Item()
{
}

Item::~Item()
{
}

void Item::init()
{
  m_interaction_box.offset = {4, 4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Item::fixed_update(double deltaTime)
{
  Entity::fixed_update(deltaTime);

  if(is_colliding(g_hero)){
    hit(-100, g_hero);
    g_camera->set_shake(.125f, .35f);
  }
}

void Item::update(double deltaTime)
{
  Entity::update(deltaTime);
}

void Item::draw()
{
}

void Item::post_update(double deltaTime)
{
}
