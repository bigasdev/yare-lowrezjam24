#include "PlayerUI.hpp"
#include "../../Core/Globals.hpp"
#include "../../Core/App.hpp"
#include "../EntityParty.hpp"
#include "../../Renderer/Atlas.hpp"
#include "../Hero.hpp"

PlayerUI::PlayerUI() {}

PlayerUI::~PlayerUI() {}

void PlayerUI::update(double deltaTime) {}

void PlayerUI::draw() {
  g_atlas->draw_text({4,54}, std::to_string(g_hero->get_inventory()->coins).c_str(), g_app->get_main_font(), {255,255,255});
  g_atlas->draw_text({38,54}, std::to_string(g_hero->get_inventory()->carrots).c_str(), g_app->get_main_font(), {255,255,255});
  g_atlas->draw_text({46,54}, std::to_string(g_hero->get_inventory()->potatos).c_str(), g_app->get_main_font(), {255,255,255});
  g_atlas->draw_text({54,54}, std::to_string(g_hero->get_inventory()->pumpkins).c_str(), g_app->get_main_font(), {255,255,255});
}
