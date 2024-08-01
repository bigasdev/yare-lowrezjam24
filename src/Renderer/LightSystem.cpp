#include "LightSystem.hpp"
#include "Atlas.hpp"
#include "Camera.hpp"

LightSystem::LightSystem(){
}

LightSystem::LightSystem(int max_lights){
}

LightSystem::~LightSystem(){
}

void LightSystem::update(double dt){
}

void LightSystem::draw(Atlas* atlas, Camera* camera){
  for(int i = 0; i < 2; i++){
    atlas->draw_pixel(100, 40 + (i*35),  255, 165, 0, 20-(i*10), camera, 1, 35);
  }
}
