#pragma once

#include <vector>
#include <memory>
#include "PartialScene.hpp"
#include "../Utils/Common.hpp"

class ImageObject;

class UIPartialScene : public PartialScene
{
public:
  UIPartialScene(App *app, Logger *logger, Cooldown *cooldown, Camera *camera);
  ~UIPartialScene();

  virtual void init() override;
  virtual void input(SDL_Event event) override;
  virtual void update(double deltaTime) override;
  virtual void draw() override;
  virtual void clean() override;

private:
  std::vector<std::unique_ptr<ImageObject>> m_image_objects;
  vec2f m_last_mouse_position;

  bool m_mouse_down = false;
  bool m_mouse_drag = false;
};
