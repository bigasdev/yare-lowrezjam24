#include "Boss.hpp"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::init()
{
  m_interaction_box.offset = {4, 4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Boss::fixed_update(double deltaTime)
{
}

void Boss::update(double deltaTime)
{
  Entity::update(deltaTime);

  switch(state)
  {
    case WALKING:
      walking_state(deltaTime);
      break;
    case HIT_STATE:
      hit_state(deltaTime);
      break;
    case INVICIBLE_STATE:
      invicible_state(deltaTime);
      break;
    case RAGE_STATE:
      rage_state(deltaTime);
      break;
  }
}

void Boss::draw()
{
  Entity::draw();
}

