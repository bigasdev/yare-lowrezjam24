#pragma once
#ifndef AFFECT_MANAGER_CPP
#define AFFECT_MANAGER_CPP

enum Affect { NORMAL = 0, STUN = 1, BLEEDING = 2, POISONED = 3, HEALED = 4 };

class AffectManager {
public:
  AffectManager();
  ~AffectManager();

  Affect get_curr_affect();
  void set_affect(Affect affect, float cd);
  void update(double dt);

private:
  float m_curr_timer = 0;
  float m_cd = 0;
  
  Affect m_curr_affect = Affect::NORMAL;
};

#endif
