#include "GarbageCollector.hpp"
#include "../Entity/EntityParty.hpp"
#include "../Utils/Common.hpp"
#include "../Core/Globals.hpp"
#include "../Core/Fort.hpp"
#include "../Utils/Vec.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/Projectile.hpp"

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector() {}

void GarbageCollector::update() {
  // entity cleanup
  auto is_dead_entity = [&](Entity *e) { return e->get_current_life() <= 0; };
  auto finish_function_entity = [&](Entity *e) { e->set_enable(true); };
  Vec::remove_vec_element_if<Entity *>(g_fort->party(), is_dead_entity,
                                       finish_function_entity);
}

