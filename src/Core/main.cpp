#include "../Utils/FDebug.hpp"
#include "App.hpp"
#include "SDL.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif
#include <memory>

// Fps
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;
const double desiredFPS = 60.0;
const double frameTime = 1.0 / desiredFPS;
double accumulatedTime = 0;

Uint32 start_time, frame_time;
float fps;

const float ALPHA = 0.1f;
float smoothed_fps = 0.0f;
// App
std::unique_ptr<App> mApp;

void mainloop() {
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
    mApp->fixed_update(frameTime);

    accumulatedTime -= frameTime;
  }
  mApp->update(frameTime);
  mApp->post_update(frameTime);

  mApp->render();
  // Framerate calculation
  frame_time = SDL_GetTicks() - start_time;
  fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;

  smoothed_fps = (ALPHA * fps) + ((1.0f - ALPHA) * smoothed_fps);

  // Sending the fps to the app so it can be displayed
  mApp->set_fps(smoothed_fps);

  mApp->load();
#ifdef __EMSCRIPTEN__
  if(!mApp->running()) {
    emscripten_cancel_main_loop();
  }
#endif
}

// Initialization of the app and calling all the core functions
int main(int args, char *argv[]) {
  mApp = std::make_unique<App>();
  F_Debug::log("App created!");

  mApp->init("Fortress framework", SDL_WINDOWPOS_CENTERED,
             SDL_WINDOWPOS_CENTERED, 640, 640, false, false);
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
