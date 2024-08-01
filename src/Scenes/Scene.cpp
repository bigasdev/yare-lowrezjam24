#include "Scene.hpp"
#include "../Core/App.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Resources/Resources.hpp"
#include "../Entity/Entity.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Tools/Logger.hpp"
#include "../Utils/Mouse.hpp"
#include "PartialScene.hpp"

Scene::Scene(App* app, Logger* logger, Cooldown* cooldown, Camera* camera)
{
	m_app = app;
	m_logger = logger;
	m_cd = cooldown;
	m_camera = camera;

	m_resources = app->get_resources();
	m_atlas = app->get_atlas();
}

void Scene::init()
{
}

void Scene::input(SDL_Event event)
{
}

void Scene::fixed_update(double deltaTime)
{
}

void Scene::update(double deltaTime)
{
}

void Scene::post_update(double deltaTime)
{
}

void Scene::draw()
{
}

void Scene::clean()
{
}
