#pragma once

#include "SDL.h"

class App;
class Atlas;
class Camera;
class Cooldown;
class Resources;
class Logger;

//the scene class, we'll use this to create the behaviours of our app.
class PartialScene {
public:
	PartialScene(App* app, Logger* logger, Cooldown* cooldown, Camera* camera);

	virtual void init();
	virtual void input(SDL_Event event);
	virtual void update(double deltaTime);
	virtual void draw();
	virtual void clean();

protected:
	App* m_app = nullptr;

	//tools
	Logger* m_logger = nullptr;
	Cooldown* m_cd = nullptr;
	Camera* m_camera = nullptr;
	Resources* m_resources = nullptr;
	Atlas* m_atlas = nullptr;
};
