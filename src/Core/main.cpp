#include "../Utils/FDebug.hpp"
#include "App.hpp"
#include "SDL.h"
#include "SDL_timer.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif
#include <memory>

// Fps
Uint64 lastTick = 0;
double deltaTime = 0;
#ifndef __EMSCRIPTEN__
Uint64 currentTick = SDL_GetPerformanceCounter();
const double desiredFPS = 60.0;
#else 
Uint64 currentTick = SDL_GetTicks();
const double desiredFPS = 15.0;
#endif
const double frameTime = 1.0 / desiredFPS;
double accumulatedTime = 0;

Uint32 start_time, frame_time;
float fps;

const float ALPHA = 0.1f;
float smoothed_fps = 0.0f;
// App
std::unique_ptr<App> mApp;

void mainloop() {
#ifndef __EMSCRIPTEN__
  // Gathering the fps before everything so it can calculate the difference
  // for the framerate;
  lastTick = currentTick;
  currentTick = SDL_GetPerformanceCounter();
  deltaTime = (double)((currentTick - lastTick) /
                       (double)SDL_GetPerformanceFrequency());

  start_time = SDL_GetTicks();

  // Core functions
  // The core functions are all called inside the app, more functionality is
  // added to the app class Through the scenes
  accumulatedTime += deltaTime;

  mApp->handle_events();
  while (accumulatedTime >= frameTime) {
    mApp->fixed_update(deltaTime);

    accumulatedTime -= frameTime;
  }
  mApp->update(deltaTime);
  mApp->post_update(deltaTime);

  mApp->render();
  // Framerate calculation
  frame_time = SDL_GetTicks() - start_time;
  fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;

  smoothed_fps = (ALPHA * fps) + ((1.0f - ALPHA) * smoothed_fps);

  // Sending the fps to the app so it can be displayed
  mApp->set_fps(smoothed_fps);
#endif
#ifdef __EMSCRIPTEN__
  double new_time = SDL_GetTicks();
  double frame_time = new_time - currentTick;

  if (frame_time > frameTime)
    frame_time = frameTime;

  currentTick = new_time;
  accumulatedTime += frame_time;

  mApp->handle_events();
  while (accumulatedTime >= frame_time) {
    mApp->fixed_update(frame_time);
    accumulatedTime -= frame_time;
  }
  mApp->update(frame_time);

  mApp->post_update(frame_time);
  mApp->render();

  frame_time = SDL_GetTicks() - currentTick;
  fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
  smoothed_fps = (ALPHA * fps) + ((1.0f - ALPHA) * smoothed_fps);
  mApp->set_fps(smoothed_fps);
#endif

  mApp->load();
#ifdef __EMSCRIPTEN__
  if (!mApp->running()) {
    emscripten_cancel_main_loop();
  }
#endif
}

// Initialization of the app and calling all the core functions
int main(int args, char *argv[]) {
  mApp = std::make_unique<App>();
  F_Debug::log("App created!");
  int width = 128;
  int height = 128;

#ifdef __EMSCRIPTEN__
  width = 448;
  height = 448;
#endif

  mApp->init("Fortress framework", SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED, width, height, false, false);
  F_Debug::log("App initialized!");
  F_Debug::log_group("App window size",
                     std::to_string(mApp->get_window_size().x) + "x" +
                         std::to_string(mApp->get_window_size().y));

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainloop, 0, 1);
#endif

#ifndef __EMSCRIPTEN__
  while (mApp->running()) {
    mainloop();
  }
#endif

  mApp->clean();

  return 0;
}
