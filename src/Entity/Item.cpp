#include "Item.hpp"
#include "../Tools/Cooldown.hpp"

Item::Item()
{
}

Item::Item(Resources* _resources, float _scale)
{
  Sprite _sprite;
  if (_resources != nullptr)
    _sprite.texture = _resources->get_aseprite_texture("framework");

  _sprite.xpu = 11;
  _sprite.ypu = 10;
  _sprite.x = 0;
  _sprite.y = 0;

  m_parent_scale = _scale;

  m_current_sprite = _sprite;

  m_affect_manager = new AffectManager();
  m_entity_cd = new Cooldown();
}

Item::~Item()
{
}

void Item::update(double deltaTime)
{
  if(m_hero != nullptr){
    if(is_colliding(m_hero)){
      kill();
    }
  }
}
