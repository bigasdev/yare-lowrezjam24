#pragma once
#include <functional>
#include <stdio.h>
#include <SDL.h>

#ifdef F_ENABLE_IMGUI
#endif
namespace GUI {
	void setup(SDL_Window *window, SDL_Renderer *renderer);
	void event(SDL_Event event);
	void draw(std::function<void()> function);
	void clean();

	//util functions
	void set_focus();
}

