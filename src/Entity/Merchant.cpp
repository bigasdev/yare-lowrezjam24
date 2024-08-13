#include "Merchant.hpp"
#include "../Core/App.hpp"
#include "../Core/Fort.hpp"
#include "../Renderer/Atlas.hpp"
#include "../Renderer/Camera.hpp"
#include "../Renderer/ParticleSystem.hpp"
#include "../Tools/Cooldown.hpp"
#include "../Utils/Gizmos.hpp"
#include "EntityParty.hpp"
#include "Hero.hpp"
#include "SDL_render.h"
#include "UI/PlayerUI.hpp"
#include <string>

SDL_Texture** concept_text;

Merchant::Merchant() {}

Merchant::~Merchant() {}

void Merchant::init() {
  concept_text = g_resources->get_aseprite_texture("concept");
  m_current_sprite.texture = concept_text;

  m_current_sprite.xpu = 16;
  m_current_sprite.ypu = 16;
  m_current_sprite.x = 1;
  m_current_sprite.y = 1;
  set_life(100, 100);

  m_interaction_box.offset = {0, 0};
  m_interaction_box.scale = {16, 16};
  m_collision_box.scale = {8, 8};

  SpriteAnimation idle = SpriteAnimation{"idle", {1, 1}, 2, .5f,
                                         &m_current_sprite};
  add_sprite_animation(idle);
  set_animation("idle");
}

void spawn_compost(Merchant* merchant) {
  auto compost =
      g_fort->recruit<Merchant>(g_resources, g_atlas->get_game_scale());
  compost->set_pos(merchant->get_pos().x + rnd(-5, 5), merchant->get_pos().y);
  compost->init();
  compost->set_speed(400);
  compost->set_life(100, 100);
  compost->set_friction(0.98f);
  compost->move_dir({rnd(-15.f, 15.f), rnd(-15.f, 15.f)});
}

void Merchant::fixed_update(double deltaTime) {
  Entity::fixed_update(deltaTime);
  if (is_interacting(g_hero) && !shuffling_state) {
    interact_range = true;

    if (g_hero->has_interact()) {
      if (g_hero->get_inventory()->coins < 25) {
        g_player_ui->set_dialogue("Need 25 coins!");
      } else {
        g_hero->get_inventory()->coins -= 25;
        shuffling_state = true;
      }
    }
  } else {
    interact_range = false;
  }

  if (shuffling_state && shuffle_ticks < SHUFFLE_TICKS) {
    if (!m_entity_cd->has_state("shuffle")) {
      m_entity_cd->set_state("shuffle", SHUFFLE_CD);

      shuffled_amt = d20();

      shuffle_ticks++;
      g_camera->set_shake(35.f, .1f);
      if (shuffle_ticks == SHUFFLE_TICKS) {
        m_entity_cd->set_state("end_shuffle", 1.5f, [&]() {
          g_camera->set_shake(60.5f, .15f);
          shuffling_state = false;
          shuffle_ticks = 0;

          if (shuffled_amt == 0) {
            g_player_ui->set_dialogue("Unlucky");
            return;
          }

          if (shuffled_amt <= 5) {
            g_player_ui->set_dialogue("You got 1 compost!");

            spawn_compost(this);
          }

          if (shuffled_amt > 5 && shuffled_amt <= 10) {
            g_player_ui->set_dialogue("You got 2 compost!");

            for(int i = 0; i < 2; i++)
              spawn_compost(this);
          }

          if (shuffled_amt > 10 && shuffled_amt <= 19) {
            g_player_ui->set_dialogue("You got 3 compost!");

            for(int i = 0; i < 3; i++)
              spawn_compost(this);
          }

          if (shuffled_amt == 20) {
            g_player_ui->set_dialogue("JACKPOT!");

            for(int i = 0; i < 5; i++)
              spawn_compost(this);
          }
        });
      }
    }
  }
}

void Merchant::update(double deltaTime) { Entity::update(deltaTime); }

void Merchant::draw() {
  Entity::draw();

  if (shuffling_state) {
    g_atlas->draw_texture_from_sheet(*concept_text, get_pos() + vec2f{2,-8}, {16,16,3,1}, g_camera );
    g_atlas->draw_text(
        get_pos() + vec2f{13, 5}, std::to_string(shuffled_amt).c_str(),
        g_app->get_main_font(), {255, 255, 255}, 1, 128, g_camera);
  }
}

void Merchant::post_update(double deltaTime) { Entity::post_update(deltaTime); }
