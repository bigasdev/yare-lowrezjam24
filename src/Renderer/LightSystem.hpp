#pragma once

class Atlas;
class Camera;

class LightSystem{
public:
  LightSystem();
  LightSystem(int max_lights);
  ~LightSystem();

  void update(double dt);
  void draw(Atlas* atlas, Camera* camera);

private:

};
