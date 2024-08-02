// default
#include <list>

#include "../Renderer/AppGui.hpp"
#include "../Renderer/Camera.hpp"
#include "../Resources/AssetData.hpp"
#include "../Resources/Resources.hpp"
#include "../Scenes/Scenes.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Tools/Logger.hpp"
#include "../Utils/Common.hpp"
#include "../Utils/FDebug.hpp"
#include "../Utils/Math.hpp"
#include "../renderer/Atlas.hpp"
#include "App.hpp"
#include "Globals.hpp"
#include "SDL_hints.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "SDL_version.h"
#include "SDL_video.h"
#include <string>

// global variable
bool debug_mode = false;

// Core functionality
Logger *m_logger = nullptr;
Cooldown *m_cd = nullptr;
Camera *m_camera = nullptr;

// Scenes
Scene *m_current_scene = nullptr;
Scene *m_next_scene = nullptr;

TTF_Font *s_main_font;

// Ideally this class should never be touched
// The important values will be exposed from the other scenes

// ALL the features should be done inside their own scene

App::App() { std::cout << "Instantied App!..." << std::endl; }

App::~App() {}

void App::init(const char *title, uint32_t xpos, uint32_t ypos, uint32_t width,
               uint32_t height, bool fullscreen, bool splash_screen) {
  // This can be edited to add more flags to the window, like borderless etc
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (fullscreen) {
    window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI |
                          SDL_WINDOW_FULLSCREEN_DESKTOP);
  }

  // SDL Initialization
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "App initialized!..." << std::endl;
    m_window = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags);
    int h = 0, w = 0;
    SDL_GetWindowSize(m_window, &h, &w);
    SDL_SetWindowMaximumSize(m_window, 640,640);
    // ensure the window cant be so small
    // SDL_SetWindowMinimumSize(m_window, w, h);
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

    auto *m_version = new SDL_version();
    SDL_GetVersion(m_version);

    std::cout << "SDL Version: " << (int)m_version->major << "."
              << (int)m_version->minor << "." << (int)m_version->patch
              << std::endl;

    // This is true if the windows was created
    if (m_window) {
      std::cout << "Window created!..." << std::endl;
      F_Debug::log("Window created!...");
    }
    m_window_size = vec2f(h, w);

    int rendererFlags = SDL_RENDERER_ACCELERATED;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "SDL could not initialize\n");
      F_Debug::error("SDL could not initialize");
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != IMG_INIT_PNG | IMG_INIT_JPG) {
      fprintf(stderr, "SDL_image could not initialize\n");
      F_Debug::error("SDL_image could not initialize");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);

    // This is true if the renderer was created
    if (m_renderer) {
      SDL_SetRenderDrawColor(m_renderer, 50, 40, 0, 255);
      std::cout << "Renderer created!..." << std::endl;
      F_Debug::log("Renderer created!...");
      m_has_splash_screen = splash_screen;

      // Initializing the GUI
      TTF_Init();

      m_camera = new Camera(nullptr, &m_window_size, {64, 64});
      m_atlas_ptr = new Atlas(m_renderer, &m_camera->s_scale);

      s_main_font = TTF_OpenFont("res/font/pixolleta.ttf", 10);
      F_Debug::log("Loaded atlas and fonts!...");
    }
    m_is_running = true;
  } else {
    m_is_running = false;
  }
}

void App::load() {
  if (m_is_loaded)
    return;
  // loading resources
  {
    GUI::setup(m_window, m_renderer);
    F_Debug::setup_crash_handlers();

    m_resources_ptr = new Resources(m_renderer);
    m_cd = new Cooldown();

    m_logger = new Logger(m_resources_ptr->GetAsset("logger")->GetTexture());
    m_logger->init(m_atlas_ptr, s_main_font, vec2f(46, 14));

    F_Debug::log("Loaded resources and utils!...");

    // Starting scenes
    if (m_has_splash_screen) {
      m_current_scene = new IntroScene(this, m_logger, m_cd, m_camera);
    } else {
#if F_ENABLE_DEBUG
      m_current_scene = new MainScene(this, m_logger, m_cd, m_camera);
#else
      m_current_scene = new MainScene(this, m_logger, m_cd, m_camera);
#endif
    }
    m_next_scene = new GameScene(this, m_logger, m_cd, m_camera);

    m_is_loaded = true;
    F_Debug::log("Adding components to globals");
    g_app = this;
    g_camera = m_camera;
    g_resources = m_resources_ptr;
    g_atlas = m_atlas_ptr;
    F_Debug::log("Finished loading!...");
    F_Debug::log_group("Loading time", std::to_string(SDL_GetTicks()) + "ms");
    F_Debug::log("----------------------------------");
    m_current_scene->init();
  }
}
// FIX: remove this later
int z_camera = 2;
std::vector<vec2i> resolutions = {{128, 128}, {192, 192},
                                  {256, 256}, {320, 320}, 
                                  {384, 384},             
                                  {448, 448},             
                                  {512, 512},             
                                  {576, 576},             
                                  {640, 640}};

int App::find_res(int w, int h){
  int idx = 1;
  int minDiff = Math::abs(w - resolutions[0].x) + Math::abs(h - resolutions[0].y);

  for(int i = 1; i < resolutions.size(); i++){
    int diff = Math::abs(w - resolutions[i].x) + Math::abs(h - resolutions[i].y);
    if(diff < minDiff){
      minDiff = diff;
      idx = i;
    }
  }

  return idx;
}

// This function will be the core of all the events that some scripts can
// require And will be responsible for listening to the inputs
void App::handle_events() {
  if (!m_is_loaded)
    return;

  SDL_Event event;
  SDL_PollEvent(&event);

  GUI::event(event);
  m_current_scene->input(event);

  switch (event.type) {
  case SDL_WINDOWEVENT:
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
      // updating window size
      {
        int h = 0, w = 0;
        SDL_GetWindowSize(m_window, &h, &w);
        z_camera = find_res(h, w) + 1;
        m_window_size.x = h;
        m_window_size.y = w;
      }
    }
    break;

  case SDL_QUIT:
    m_is_running = false;
    break;

  case SDL_KEYDOWN:
    // moving gathering input
    // mCurrentScene->Input(event.key.keysym.scancode);
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_D:
#if F_ENABLE_DEBUG
      // m_logger->log("Debug mode: " + std::to_string(debug_mode));
#endif
      break;
    case SDL_SCANCODE_A:

      break;
    case SDL_SCANCODE_W:

      break;
    case SDL_SCANCODE_S:
      // m_logger->log("You pressed S");

      break;
    case SDL_SCANCODE_E:
      // m_logger->log("Testing the logger");
      // ChangeToNextScene();
      break;
    case SDL_SCANCODE_ESCAPE:
#if F_ENABLE_DEBUG
      m_is_running = false;
#endif
      break;
    }
    break;

  case SDL_KEYUP:
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_D:

      break;
    case SDL_SCANCODE_A:

      break;
    case SDL_SCANCODE_W:

      break;
    case SDL_SCANCODE_S:

      break;
    }
    break;

  default:
    break;
  }
}

void App::fixed_update(double deltaTime) {
  if (!m_is_loaded)
    return;

  m_current_scene->fixed_update(deltaTime);
}

void App::update(double deltaTime) {
  if (!m_is_loaded)
    return;

  m_cd->update(deltaTime);
  m_logger->update(deltaTime);
#if F_ENABLE_DEBUG
  m_resources_ptr->aseprite_hot_reload();
#endif

  if (m_current_scene != nullptr)
    m_current_scene->update(deltaTime);
}

void App::post_update(double deltaTime) {
  if (!m_is_loaded)
    return;

  if (m_current_scene != nullptr)
    m_current_scene->post_update(deltaTime);
}

// The core sdl renderer, this will encapusalate the scene rendering so there is
// no need to clear and call the color inside the scenes
void App::render() {
  SDL_SetRenderDrawColor(m_renderer, m_window_color.x, m_window_color.y,
                         m_window_color.z, 255);
  SDL_RenderClear(m_renderer);
  auto x = static_cast<int>(m_window_size.x - (64*z_camera))/2;
  auto y = static_cast<int>(m_window_size.y - (64*z_camera))/2;
  SDL_Rect viewport = {x/z_camera, y/z_camera, 64, 64};
  SDL_RenderSetViewport(m_renderer, &viewport);
  SDL_RenderSetScale(m_renderer, z_camera, z_camera);
  // rendering loop here
  if (m_is_loaded) {
    // scene drawing
    if (m_current_scene != nullptr)
      m_current_scene->draw();

    // logger rendering
    m_logger->draw();

    m_atlas_ptr->draw_text({2, 2}, std::to_string(Math::round(m_fps)).c_str(),
                           s_main_font, {255, 255, 255, 255}, 1.f);
  } else {
    m_atlas_ptr->draw_text(
        {(m_window_size.x - 70) / 2, (m_window_size.y - 50) / 2}, "Loading...",
        s_main_font, {255, 255, 255, 255});
  }
  SDL_RenderPresent(m_renderer);
}

void App::clean() {
  GUI::clean();
  m_current_scene->clean();
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
  TTF_Quit();
  SDL_Quit();
  F_Debug::log("App cleaned!");
  F_Debug::write_to_file("log.txt");
}

void App::change_scene(Scene *scene) {
  m_current_scene->clean();
  m_current_scene = scene;
  m_current_scene->init();
}

void App::restart_scene() {
  m_current_scene->clean();
  m_current_scene->init();
}

void App::change_to_next_scene() {
  m_current_scene->clean();
  m_current_scene = m_next_scene;
  m_current_scene->init();
}

void App::change_background_color(vec3f color) { m_window_color = color; }

vec2f App::get_window_size() { return m_window_size; }

TTF_Font *App::get_main_font() { return s_main_font; }

bool App::get_mouse_state() { return m_is_mouse_down; }

float App::get_fps() { return m_fps; }

void App::set_fps(float fps) { m_fps = Math::clamp(0.f, fps, 120.f); }

SDL_Window *App::get_window() { return m_window; }

SDL_Renderer *App::get_renderer() { return m_renderer; }

Resources *App::get_resources() { return m_resources_ptr; }

Atlas *App::get_atlas() { return m_atlas_ptr; }

bool App::running() { return m_is_running; }
