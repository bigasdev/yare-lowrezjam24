#pragma once

#include "SDL.h"
#include "SDL_gpu.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include "../Utils/Common.hpp"

class Scene;
class Resources;
class Atlas;
class SoundManager;
//global variables
extern bool debug_mode;

class App {

public:

	App();
	~App();

	void init(const char* title, uint32_t xpos, uint32_t ypos, uint32_t width, uint32_t height, bool fullscreen, bool splash_screen);
	void load();
	void handle_events();
  void fixed_update(double deltaTime);
	void update(double deltaTime);
  void post_update(double deltaTime);
	void render();
	void clean();

	//Functionality
	void change_scene(Scene* scene);
  void restart_scene();
	void change_to_next_scene();

	//Util methods
	void change_background_color(vec3f color);

	//Local getters
  int find_res(int w, int h);
  int get_current_res();
	vec2f get_window_size();
  float* get_window_x() { return &m_window_size.x; }
  float* get_window_y() { return &m_window_size.y; }

	//System methods
	float get_fps();
	void set_fps(float fps);
	bool running();

	//Getters
	SDL_Window* get_window();
	SDL_Renderer* get_renderer();
  GPU_Target* get_gpu() { return m_gpu; }
	Resources* get_resources();
	Atlas* get_atlas();
	TTF_Font* get_main_font();
	bool get_mouse_state();


private:
	bool m_is_running = false;
	bool m_is_loaded = false;
	bool m_has_splash_screen = true;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
  GPU_Target* m_gpu = nullptr;
	Resources* m_resources_ptr = nullptr;
  SoundManager* m_sound_manager = nullptr;
	Atlas* m_atlas_ptr = nullptr;

	//Local
	vec2f m_window_size = vec2f(0,0);
	vec3f m_window_color = vec3f(26, 25, 50);

	//System
	int m_fps = 0;
	bool m_is_mouse_down = false;
};
