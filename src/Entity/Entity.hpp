#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "../Utils/Common.hpp"
#include "../Utils/Sprite.hpp"
#include "AffectManager.hpp"
#include "../Core/Globals.hpp"

#include "../Utils/random.hpp"
#include <functional>

using Random = effolkronium::random_static;

#include <string>
#include <vector>
#include <functional>

class Resources;
class EntityRenderer;
class Camera;
class Rune;
class Cooldown;
class AffectManager;
class Sprite;

// main class for the entities, in our app everything that will be displayed and
// have interaction is an entity
class Entity
{
public:
  // constructors, so a entity might not be able to access app if we want to.
  Entity();
  Entity(Resources *_resources, float _scale);
  Entity(vec2f _pos, vec2f _scale, SDL_Texture *_texture, int _uid);

  // setters
  void set_pos(float xpos, float ypos);
  void set_scale(float w, float h);
  void set_frame(vec2f frame);
  void set_angle(float _angle);
  void set_life(float _maxLife, float _life);
  void set_texture(SDL_Texture *_texture);
  void set_collision_box(CollisionBox2D _collision_box);
  void set_renderer(EntityRenderer *_renderer);
  void set_current_sprite(Sprite _sprite);
  void set_visible(bool _visible);
  void set_uid(int _uid);
  void set_enable(bool _enable) { m_enabled = _enable; }

  // animation stuff
  void add_sprite_animation(SpriteAnimation _animation);
  void set_animation(std::string _name);

  void change_state(State _state, const char *reason);
  void change_visibility(bool _visible);
  void set_move(bool _moving);
  void set_cd(std::string _cd, float _timer, std::function<void()> _event);
  void set_facing_dir(bool _facing_right);

  // input stuff
  void input(SDL_Event event);

  // getters
  SDL_Texture *get_texture();
  Sprite *get_current_sprite();
  SDL_Rect get_current_frame();
  vec2f get_pos();
  vec2f get_scale();
  float get_speed();
  float get_angle();
  CollisionBox2D get_collision_box(float _scale = 1);
  CollisionBox2D get_interaction_box(float _scale = 1);
  int get_uid();
  Affect get_affect();
  bool is_visible();
  bool is_moving();
  bool is_enabled() { return m_enabled; }
  bool has_cd(std::string _cd);

  // squash
  void set_squash_x(float x);
  void set_squash_y(float y);
  void squash_update(double deltaTime);

  // move stuff
  void set_velocity(vec2f _velocity) { m_velocity = _velocity; }
  void set_speed(float _speed) { m_speed = _speed; }
  void set_friction(float _friction) { m_friction = _friction; }
  void move_to(Entity* en);
  void move_dir(vec2f dir);

  int d20();

  // utils
  bool is_close_to_pos(vec2f pos, float radius);
  bool is_colliding(Entity* en);
  bool is_interacting(Entity* en);

  // functionality methods
  virtual void init();
  void hit(float damage, Entity *from);
  virtual void fixed_update(double deltaTime);
  virtual void update(double deltaTime);
  virtual void post_update(double deltaTime);
  virtual void draw();
  void set_affect(Affect affect, float cd);
  bool is_alive();
  void kill();
  void set_death_callback(std::function<void()> _on_death);
  float get_current_life();
  void apply_filter();


  // a default spriteanimation
  //  = SpriteAnimation("default",
  // std::vector<std::string>{"default", "default1"}, nullptr);

  bool m_visible = true;
  Tag m_tag = Tag::NONE;

protected:
  // global variables that every entity should be able to call
  App *m_app = g_app;
  Atlas *m_atlas = g_atlas;
  Resources *m_resources = g_resources;
  Camera *m_camera = g_camera;
  Fort *m_fort = g_fort;
  CastleDBConverter *m_castledb = g_castledb;
  ProjectileSystem *m_projectile_system = g_projectile_system;
  ParticleSystem *m_particle_system = g_particle_system;
  

  // controller variables
  int m_uid;
  float m_parent_scale = 1;
  bool m_enabled = true;

  // draw/pos stuff
  EntityRenderer *m_renderer;
  Sprite m_current_sprite = Sprite();
  vec2f m_pos;
  float m_angle = 0;
  vec2f m_scale = vec2f(1, 1);
  SDL_Rect m_current_frame = {0, 0, 0, 0};
  SDL_Texture *m_texture;
  bool m_moving = false;
  std::vector<SpriteAnimation> m_animations;
  SpriteAnimation m_current_animation;

  // squash
  int dir = 1;
  float m_spr_squash_x = 1;
  float m_spr_squash_y = 1;

  //speed/movement stuff
  vec2f m_velocity;
  float m_speed = 8;
  float m_friction = 1;

  Cooldown *m_entity_cd = nullptr;
  AffectManager *m_affect_manager = nullptr;

  // parameters
  CollisionBox2D m_collision_box = CollisionBox2D({0, 0}, {0, 0});
  CollisionBox2D m_interaction_box = CollisionBox2D({0, 0}, {16, 16});
  Life m_life = Life(0, 100);
  State m_current_state = UPDATE;

  //callbacks
  std::function<void()> m_on_death;
};
#endif
