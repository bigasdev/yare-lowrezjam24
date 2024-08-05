#include "Dirt.hpp"
#include "../Core/App.hpp"
#include "../Core/Globals.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Utils/Gizmos.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include <string>

Dirt::Dirt() {}

Dirt::~Dirt() {}

void Dirt::init() {
  m_current_sprite.texture = g_resources->get_aseprite_texture("concept");

  m_current_sprite.xpu = 8;
  m_current_sprite.ypu = 8;
  m_current_sprite.x = 0;
  m_current_sprite.y = 2;
  set_life(100, 100);

  m_interaction_box.offset = {4,4};
  m_interaction_box.scale = {8, 8};
  m_collision_box.scale = {8, 8};
}

void Dirt::fixed_update(double deltaTime) {
  if (is_interacting(g_hero)) {
    interact_range = true;

    if(g_hero->has_interact()){
      if(!has_plant) has_plant = true;
    }
  } else {
    interact_range = false;
  }
}

void Dirt::update(double deltaTime) { Entity::update(deltaTime); }

void Dirt::draw() {
#if F_ENABLE_DEBUG
  Gizmos::draw_rect(get_interaction_box().offset,
                    get_interaction_box().scale, g_atlas, {255, 0, 0}, 85,
                    g_camera);
#endif
  if (interact_range) {
    auto str = "Crop : " + std::to_string(m_uid);
    g_atlas->draw_text({10, 55}, str.c_str(), g_app->get_main_font(),
                       {255, 255, 255});
  }

  if(has_plant){
    m_atlas->draw_texture_from_sheet(*m_current_sprite.texture, get_pos()+vec2f(0,-4), {8,8,0,3}, g_camera);
  }
}

void Dirt::post_update(double deltaTime) {}

void Dirt::animation_manager() {}
