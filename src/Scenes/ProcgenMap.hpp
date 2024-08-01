#pragma once
#ifndef _ProcgenMap_HPP
#define _ProcgenMap_HPP
#include "Scene.hpp"

class ProcgenMap : public Scene {
public:
	ProcgenMap(App* app, Logger* logger, Cooldown* cooldown, Camera* camera);

	void init();
	void update(double deltaTime);
	void draw();
	void input(SDL_Event event);
	void clean();
	void load_assets();

	void ui();

private:

};

#endif
