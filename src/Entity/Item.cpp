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
  m_interaction_box.offset = {0, 0};
  m_interaction_box.scale = {16, 16};
  m_collision_box.scale = {16, 16};

  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");
  m_current_sprite.xpu = 11;
  m_current_sprite.ypu = 16;
  m_current_sprite.x = 0;
  m_current_sprite.y = 8;

  int r = rnd(0,3);
  type = static_cast<ItemType>(r);
}
void Item::set_coin(){

  m_current_sprite.xpu = 16;
  m_current_sprite.y = 13;
  type = ItemType::COIN;
}

void Item::fixed_update(double deltaTime)
{
  Entity::fixed_update(deltaTime);

  if(is_colliding(g_hero)){
    hit(-100, g_hero);
    g_camera->set_shake(3.125f, .35f);

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
      case ItemType::COIN:
        g_hero->get_inventory()->coins += 1;
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
