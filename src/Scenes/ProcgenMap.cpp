#include "ProcgenMap.hpp"
#include "../Utils/FDebug.hpp"
#include "../Utils/PixelDrawer.hpp"
#include <string>
#include <vector>
#if F_ENABLE_IMGUI
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_sdl.h"
#endif
#include "../Renderer/AppGui.hpp"
#include "../Core/App.hpp"
#include "../Tools/Logger.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Math.hpp"
#include "../Renderer/Atlas.hpp"

enum Direction { LEFT, RIGHT, TOP, BOTTOM };

struct Room {
  int id;
  int x;
  int y;
  int width;
  int height;
  std::unique_ptr<Room> left, right, top, bottom;
};

struct Map {
  int x;
  int y;
  int width;
  int height;

  std::vector<std::unique_ptr<Room>> rooms;
};

Map m_current_map;
int m_seed;

void generate_map() {
  //
  m_current_map.rooms.clear();
  m_current_map.x = 300;
  m_current_map.y = 400;
  m_current_map.width = 400;
  m_current_map.height = 200;

  Random::seed(m_seed);

  int side_rooms = (m_current_map.width / 20) / 2;
  int top_rooms = (m_current_map.height / 20) / 2;

  int right = rnd(1, side_rooms);
  int left = rnd(1, side_rooms);
  int top = rnd(1, top_rooms);
  int bottom = rnd(1, top_rooms);

  int steps = right + left + top + bottom;
}

ProcgenMap::ProcgenMap(App *app, Logger *logger, Cooldown *cooldown,
                       Camera *camera)
    : Scene(app, logger, cooldown, camera) {}

void ProcgenMap::load_assets() {
  // example of creating the hero
  // mHero = new Hero(Vector2f(250, 100), Vector2f(8*3, 10*3),

  // creating an idle sprite animation and loading it to the hero
  // std::vector<std::string> idleFrames = { "hero.png", "hero1.png",
  // "hero2.png", "hero3.png", "hero4.png", "hero5.png" }; double timer =
  // 0.3f; mHero->AddSpriteAnimation(SpriteAnimation("idle", idleFrames,
  // timer));
}

void ProcgenMap::init() {
  m_cd->set_state("init_event", .1f,
                  [&] { m_logger->log("Starting the ProcgenMap!"); });
  m_app->change_background_color(vec3f(61, 61, 61));

  //
  //
  load_assets();
  //
  generate_map();
}

void ProcgenMap::update(double deltaTime) {}
// the main ui
void ProcgenMap::ui() {
}
//FIX: spiral thingy 4fun remove this later
const double PI = 3.14159265359;
const double spiral_radius = 0;
const double spiral_rate = 0.1;

vec2f get_spiral(double tetha){
  double r = spiral_radius + spiral_rate * tetha;
  double x = r * cos(tetha);
  double y = r * sin(tetha);
  return {static_cast<float>(x), static_cast<float>(y)};
}

double tetha = 0;
double other_tetha = 0;

struct SpiralParticle{
  double tetha;
};

SpiralParticle particles[10];

void ProcgenMap::draw() {
  // ui
  GUI::draw([this]() { this->ui(); });
  auto middle = Math::mid_vec(m_app->get_window_size(), vec2f(366, 20));

  m_atlas->draw_text(middle, "HELLO WORLD", m_app->get_main_font(),
                     {255, 255, 255, 255});

  for (auto &room : m_current_map.rooms) {
    PixelDrawer::draw_rect(
        {static_cast<float>(room->x), static_cast<float>(room->y)},
        {static_cast<float>(room->width), static_cast<float>(room->height)},
        m_atlas, {255, 255, 255});
  }
  
  for(int i = 5; i < 10; i++){
    auto pos = get_spiral(particles[i].tetha);
    PixelDrawer::draw_rect(vec2f{150,150} + pos, {i,i}, m_atlas, {255,125,0}, 190 + (i*25), 1);
    particles[i].tetha += PI / (16 + (i * 6));
  }
}

void ProcgenMap::input(SDL_Event event) {
  // example of a input listening
  // mHero->Input(event);

  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN:
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:

      break;
    }

  case SDL_MOUSEBUTTONUP:
    if (event.type == SDL_MOUSEBUTTONDOWN)
      return;
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:

      break;
    }

  case SDL_KEYDOWN:
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_D: {
    }

    break;
    case SDL_SCANCODE_E: {
      m_current_map.rooms.clear();
    } break;
    case SDL_SCANCODE_P: {
    } break;

    case SDL_SCANCODE_A:

      break;
    case SDL_SCANCODE_T:

      break;
    case SDL_SCANCODE_RETURN:

      break;
    case SDL_SCANCODE_ESCAPE:

      break;
    case SDL_SCANCODE_TAB:

      break;
    }
    break;
  case SDL_KEYUP:
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_D:
      break;
    case SDL_SCANCODE_RETURN:

      break;
    case SDL_SCANCODE_TAB:

      break;
    }
    break;
  }
}

void ProcgenMap::clean() {}
