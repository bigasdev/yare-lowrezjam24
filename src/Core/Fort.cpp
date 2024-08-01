#include "Fort.hpp"

Fort::Fort() {}

Fort::~Fort() {}

std::vector<Entity *> Fort::group(Tag _tag) {
  std::vector<Entity *> group;
  for (auto &e : entities) {
    if (e->m_tag == _tag) {
      group.push_back(e);
    }
  }
  return group;
}

std::vector<Entity *> &Fort::party() { return entities; }

void Fort::destroy() { entities.clear(); }
