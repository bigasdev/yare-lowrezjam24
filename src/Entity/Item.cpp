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

    switch(type){
      case ItemType::STR:
        g_hero->get_stats()->str += 1;
        break;
      case ItemType::DEF:
        g_hero->get_stats()->def += 1;
        break;
      case ItemType::SPD:
        g_hero->get_stats()->spd += 5;
        break;
    }
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
