#include "PlayerUI.hpp"
#include "../../Core/App.hpp"
#include "../../Core/Globals.hpp"
#include "../../Renderer/Atlas.hpp"
#include "../EntityParty.hpp"
#include "../../Resources/Resources.hpp"
#include "../Hero.hpp"

PlayerUI::PlayerUI() {
  dialogue_texture = g_resources->get_aseprite_texture("concept");
}

PlayerUI::~PlayerUI() {}

void PlayerUI::update(double deltaTime) {
  if(has_dialogue){
    dialogue_timer += deltaTime;
    type_timer += deltaTime;

    if(dialogue_timer >= DIALOGUE_TIME){
      has_dialogue = false;
      dialogue_timer = 0;
      dialogue = "";
    }

    if(type_timer >= TYPE_SPEED){

      if(dialogue.size() == new_dialogue.size())return;

      dialogue += new_dialogue[dialogue.size()];
      type_timer = 0;
    }
  }
}

void PlayerUI::set_dialogue(std::string p_dialogue) {
  new_dialogue = p_dialogue;
  dialogue = new_dialogue[0];
  has_dialogue = true;
}

void PlayerUI::draw() {
  if (!has_dialogue) {
    g_atlas->draw_text({4, 54},
                       std::to_string(g_hero->get_inventory()->coins).c_str(),
                       g_app->get_main_font(), {255, 255, 255});
    g_atlas->draw_text({38, 54},
                       std::to_string(g_hero->get_inventory()->carrots).c_str(),
                       g_app->get_main_font(), {255, 255, 255});
    g_atlas->draw_text({46, 54},
                       std::to_string(g_hero->get_inventory()->potatos).c_str(),
                       g_app->get_main_font(), {255, 255, 255});
    g_atlas->draw_text(
        {54, 54}, std::to_string(g_hero->get_inventory()->pumpkins).c_str(),
        g_app->get_main_font(), {255, 255, 255});
  }else{
    g_atlas->draw_texture_from_sheet(*dialogue_texture, {20, 48}, {16,16,0,4}, nullptr, 1);
    g_atlas->draw_text({4, 54}, dialogue.c_str(), g_app->get_main_font(), {255, 255, 255});
  }
}
