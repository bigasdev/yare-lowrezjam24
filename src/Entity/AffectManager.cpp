#include "AffectManager.hpp"
#include "../Utils/FDebug.hpp"

AffectManager::AffectManager() {}

AffectManager::~AffectManager() {}

Affect AffectManager::get_curr_affect() { return m_curr_affect; }

void AffectManager::set_affect(Affect affect, float cd) {
  if(affect < m_curr_affect){
    F_Debug::log("AffectManager::set_affect: trying to set a lower affect than the current one");
    return;
  }

  F_Debug::log("AffectManager::set_affect: setting affect to " + std::to_string(affect));

  m_curr_affect = affect;
  m_cd = cd;
}

void AffectManager::update(double dt) {
  if (m_curr_affect != Affect::NORMAL) {
    m_curr_timer += dt;

    if (m_curr_timer >= m_cd) {
      m_curr_affect = Affect::NORMAL;
      m_curr_timer = 0;
    }
  }
}
