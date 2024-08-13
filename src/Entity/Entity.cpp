#include "Entity.hpp"
#include "../Core/App.hpp"
#include "../Entity/Hero.hpp"
#include "UI/EntityTooltips.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Renderer/EntityRenderer.hpp"
#include "../Resources/Resources.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Tools/Rune.hpp"
#include "../Utils/FDebug.hpp"
#include "../Utils/Math.hpp"
#include "EntityParty.hpp"
#include "SDL.h"
#include "SDL_blendmode.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include <string>

Entity::Entity() {}

Entity::Entity(Resources *_resources, float _scale) {
  Sprite _sprite;
  if (_resources != nullptr)
    _sprite.texture = _resources->get_aseprite_texture("character_atlas");

  _sprite.xpu = 11;
  _sprite.ypu = 10;
  _sprite.x = 0;
  _sprite.y = 0;

  m_parent_scale = _scale;

  m_current_sprite = _sprite;

  m_entity_cd = new Cooldown();
  m_affect_manager = new AffectManager();
  m_tooltip = new EntityTooltips();
}

void Entity::init() {
  if (m_tag == Tag::HERO) {
    g_camera->set_entity(this);
  }
}

Entity::Entity(vec2f _pos, vec2f _scale, SDL_Texture *_texture, int _uid) {
  m_pos = _pos;
  m_texture = _texture;
  m_uid = _uid;
  m_current_frame.w = _scale.x;
  m_current_frame.h = _scale.y;
}

void Entity::set_pos(float xpos, float ypos) {
  m_pos.x = xpos;
  m_pos.y = ypos;
}

void Entity::set_scale(float w, float h) {
  m_scale.x = w;
  m_scale.y = h;
}

void Entity::set_frame(vec2f frame) {
  m_current_frame.w = frame.x;
  m_current_frame.h = frame.y;
}

void Entity::set_angle(float _angle) { m_angle = _angle; }

void Entity::set_life(float _maxLife, float _life) {
  m_life = Life(_maxLife, _life);
}

void Entity::change_state(State _state, const char *reason) {
  std::cout << reason << std::endl;
  m_current_state = _state;
}

void Entity::change_visibility(bool _visible) { m_visible = _visible; }

void Entity::set_move(bool _moving) { m_moving = _moving; }

void Entity::set_cd(std::string _cd, float _timer,
                    std::function<void()> _event) {
  m_entity_cd->set_state(_cd, _timer, _event);
}

void Entity::set_facing_dir(bool _facing_right) {
  m_current_sprite.facing_right = _facing_right;
}

void Entity::set_visible(bool _visible) { m_visible = _visible; }

void Entity::set_uid(int _uid) { m_uid = _uid; }

void Entity::input(SDL_Event event) {}

SDL_Texture *Entity::get_texture() { return m_texture; }
void Entity::set_texture(SDL_Texture *_texture) {
  if (_texture == nullptr) {
    std::cout << "Texture is null" << std::endl;
    return;
  }
  m_texture = _texture;
}

void Entity::set_renderer(EntityRenderer *_renderer) { m_renderer = _renderer; }

void Entity::set_current_sprite(Sprite _sprite) { m_current_sprite = _sprite; }
void Entity::set_collision_box(CollisionBox2D _collision_box) {
  m_collision_box = _collision_box;
}

void Entity::add_sprite_animation(SpriteAnimation _animation) {
  m_animations.push_back(_animation);
}

void Entity::set_animation(std::string _name) {
  for (auto const animation : m_animations) {
    if (m_current_animation.get_name() == _name)
      return;
    if (animation.get_name() == _name) {
      F_Debug::log_group("Animation", _name);
      m_current_animation = animation;
      m_current_animation.start();
      return;
    }
  }
}

Sprite *Entity::get_current_sprite() { return &m_current_sprite; }

SDL_Rect Entity::get_current_frame() { return m_current_frame; }

vec2f Entity::get_pos() { return m_pos; }

vec2f Entity::get_scale() { return m_scale; }

float Entity::get_speed() { return m_speed; }

CollisionBox2D Entity::get_collision_box(float _scale) {
  CollisionBox2D box;
  if (_scale == 1)
    _scale = m_parent_scale;
  box.offset = {m_pos.x + m_collision_box.offset.x * _scale,
                m_pos.y + m_collision_box.offset.y * _scale};
  box.scale = {m_collision_box.scale.x * _scale,
               m_collision_box.scale.y * _scale};
  return box;
}

CollisionBox2D Entity::get_interaction_box(float _scale) {
  CollisionBox2D box;
  if (_scale == 1)
    _scale = m_parent_scale;

  box.offset = {m_pos.x + m_interaction_box.offset.x * _scale,
                m_pos.y + m_interaction_box.offset.y * _scale};
  box.scale = {m_interaction_box.scale.x * _scale,
               m_interaction_box.scale.y * _scale};
  return box;
}

float Entity::get_angle() { return m_angle; }

int Entity::get_uid() { return m_uid; }

Affect Entity::get_affect() { return m_affect_manager->get_curr_affect(); }

bool Entity::is_visible() {
  return g_camera->is_on_screen(m_pos);
}

bool Entity::is_moving() { return m_moving; }

void Entity::set_squash_x(float x) {
  m_spr_squash_x = x;
  m_spr_squash_y = 2 - x;
}

void Entity::set_squash_y(float y) {
  m_spr_squash_y = y;
  m_spr_squash_x = 2 - y;
}

void Entity::squash_update(double deltaTime) {
  m_current_frame.w = 16 * m_spr_squash_x;
  m_current_frame.h = 11 * m_spr_squash_y;

  m_spr_squash_x += (1 - m_spr_squash_x) * 1.5f * deltaTime;
  m_spr_squash_y += (1 - m_spr_squash_y) * 1.5f * deltaTime;
}

void Entity::move_to(Entity *en) {
  vec2f dir = en->get_pos() - m_pos;
  vec2f normalized = dir.normalize();
  m_velocity = normalized;
}

void Entity::move_dir(vec2f dir) {
  vec2f _dir = dir - m_pos;
  vec2f normalized = _dir.normalize();
  m_velocity = normalized;
}

int Entity::d20() {
  int value = Random::get(1, 20);
  F_Debug::log_group("D20", std::to_string(value));
  return value;
}

bool Entity::is_close_to_pos(vec2f pos, float radius) {
  return pos.x - radius < m_pos.x && m_pos.x < pos.x + radius &&
         pos.y - radius < m_pos.y && m_pos.y < pos.y + radius;
}

bool Entity::is_colliding(Entity *en) {
  CollisionBox2D box1 = get_collision_box();
  CollisionBox2D box2 = en->get_collision_box();

  return (box1.offset.x < box2.offset.x + box2.scale.x) &&
         (box1.offset.x + box1.scale.x > box2.offset.x) &&
         (box1.offset.y < box2.offset.y + box2.scale.y) &&
         (box1.offset.y + box1.scale.y > box2.offset.y);
}

  
bool Entity::is_colliding(CollisionBox2D box1, CollisionBox2D box2) {
  return (box1.offset.x < box2.offset.x + box2.scale.x) &&
         (box1.offset.x + box1.scale.x > box2.offset.x) &&
         (box1.offset.y < box2.offset.y + box2.scale.y) &&
         (box1.offset.y + box1.scale.y > box2.offset.y);
}

bool Entity::is_interacting(Entity *en) {
  CollisionBox2D box1 = get_interaction_box();
  CollisionBox2D box2 = en->get_interaction_box();

  return (box1.offset.x < box2.offset.x + box2.scale.x) &&
         (box2.offset.x < box1.offset.x + box1.scale.x) &&
         (box1.offset.y < box2.offset.y + box2.scale.y) &&
         (box2.offset.y < box1.offset.y + box1.scale.y);
}

void Entity::hit(float damage, Entity *from) {
  m_life.add(damage);
  if (m_life.value <= 0) {
    if (m_on_death != nullptr)
      m_on_death();
  }
}

void Entity::fixed_update(double deltaTime) {
  if (m_affect_manager->get_curr_affect() != Affect::STUN) {
    // movement stuff
    if (!m_velocity.zero()) {
      m_pos += m_velocity * m_speed * deltaTime;
      auto fric = Math::pow(m_friction, deltaTime);
      m_speed *= fric;
    }
  }
/*
  if(m_tag != Tag::HERO){
    if(is_colliding(g_hero)){
      hit(-100, g_hero);
      g_particle_system->grab_example(get_pos() - vec2f{10,0}, 45);
      g_camera->set_shake(.125f, .35f);
    }
  }
  */
}

void Entity::update(double deltaTime) {
  m_affect_manager->update(deltaTime);

  if (m_affect_manager->get_curr_affect() != Affect::STUN) {
    m_entity_cd->update(deltaTime);
  }

  if (m_current_animation.get_name() == "default")
    return;

  m_current_animation.update(deltaTime);

  // set_texture(m_current_animation->get_current_frame());
}

void Entity::post_update(double deltaTime) {}

void Entity::draw() {}

void Entity::set_affect(Affect affect, float cd) {
  m_affect_manager->set_affect(affect, cd);
}

bool Entity::has_cd(std::string _cd) { return m_entity_cd->has_state(_cd); }

bool Entity::is_alive() { return m_life.is_alive(); }
void Entity::kill() {
  m_life.value = 0;
  if (m_on_death != nullptr)
    m_on_death();

  delete m_entity_cd;
  delete m_affect_manager;
  delete m_tooltip;
}

void Entity::set_death_callback(std::function<void()> _on_death) {
  m_on_death = _on_death;
}

float Entity::get_current_life() { return m_life.value; }

void Entity::apply_filter() {
  SDL_SetTextureAlphaMod(*get_current_sprite()->texture, 255);
  SDL_SetTextureColorMod(*get_current_sprite()->texture, 255, 255, 255);
  SDL_SetTextureBlendMode(*get_current_sprite()->texture, SDL_BLENDMODE_BLEND);
}
