#include "PlayerUI.hpp"
#include "../../Core/App.hpp"
#include "../../Core/Globals.hpp"
#include "../../Renderer/Atlas.hpp"
#include "../EntityParty.hpp"
#include "../../Resources/Resources.hpp"
#include "../Hero.hpp"

PlayerUI::PlayerUI()
{
  dialogue_texture = g_resources->get_aseprite_texture("concept");
}

PlayerUI::~PlayerUI() {}

void PlayerUI::update(double deltaTime)
{
  if (has_dialogue)
  {
    dialogue_timer += deltaTime;
    type_timer += deltaTime;

    if (dialogue_timer >= DIALOGUE_TIME)
    {
      has_dialogue = false;
      dialogue_timer = 0;
      dialogue = "";
    }

    if (type_timer >= TYPE_SPEED)
    {

      if (dialogue.size() == new_dialogue.size())
        return;

      dialogue += new_dialogue[dialogue.size()];
      type_timer = 0;
    }
  }
}

void PlayerUI::set_dialogue(std::string p_dialogue)
{
  new_dialogue = p_dialogue;
  dialogue = new_dialogue[0];
  has_dialogue = true;
}

void PlayerUI::draw()
{
  if (!has_dialogue)
  {
    if (g_hero_state == HeroState::BATTLE)
    {
      g_atlas->draw_texture_from_sheet(*dialogue_texture, {0, 35}, {64, 16, 0, 6}, nullptr, 1, false, false);
      for (int i = 0; i < 7; i++)
      {
        g_atlas->draw_line({5, 55 + i}, {57, 55 + i}, {255, 0, 0}, 255, nullptr);
      }
    }
    else
    {
      g_atlas->draw_texture_from_sheet(*dialogue_texture, {0, 32}, {64, 16, 0, 5}, nullptr);
      g_atlas->draw_text({18, 52.5f},
                         std::to_string(g_hero->get_inventory()->coins).c_str(),
                         g_app->get_main_font(), {255, 255, 255});
      g_atlas->draw_text({50, 52.5f},
                         std::to_string(g_hero->get_inventory()->carrots).c_str(),
                         g_app->get_main_font(), {255, 255, 255});
    }
  }
  else
  {
    g_atlas->draw_texture_from_sheet(*dialogue_texture, {0, 35}, {64, 16, 0, 4}, nullptr, 1, false, false);
    g_atlas->draw_text({4, 45}, dialogue.c_str(), g_app->get_main_font(), {255, 255, 255}, 1, 68);
  }
}
