#ifndef FORT_HPP
#define FORT_HPP

#include "../Entity/EntityParty.hpp"
#include "../Entity/Entity.hpp"
#include <vector>
#include <memory>

class Resources;

class Fort {
public:
  Fort();
  ~Fort();

  template <typename T> T *recruit(Resources *_res, float _scale) {
    auto e = new T(_res, _scale);
    e->set_uid(entities.size());
    entities.push_back(e);
    return static_cast<T *>(entities.back());
  }

  std::vector<Entity *> group(Tag _tag);
  std::vector<Entity* > &party();
  void destroy();

private:
  std::vector<Entity*> entities;
};

#endif
