#include "Input.h"

void Input::update(bool& running, Render* render, SDL_Renderer* renderer, Player* player, Chatbox* chatbox, std::vector<NPC*> npcs, int& game_state, std::tuple<int, int> window_scale) {

	SDL_PollEvent(&e);

	if (e.type == SDL_QUIT) {

		running = false; 
		
	}

	if (e.type == SDL_KEYDOWN) { 

		if (game_state == 4) { // IF PLAYING 

			if (e.key.keysym.sym == SDLK_d && !player->get_right() && !player->get_left() && !player->get_attack()) {

				player->move_right(true);
				player->reset_animation();

			}

			else if (e.key.keysym.sym == SDLK_a && !player->get_left() && !player->get_right() && !player->get_attack()) {

				player->move_left(true);
				player->reset_animation();

			}

			if (e.key.keysym.sym == SDLK_LSHIFT && !player->get_sprint()) {


				player->set_sprint(true);
				player->reset_animation();

			}

			if (e.key.keysym.sym == SDLK_w && !player->get_attack()) {

				if (!player->get_jump()) {


					player->set_jump(true);
					player->reset_animation();

				}

			}

			if (e.key.keysym.sym == SDLK_SPACE) {

				if (!player->get_attack() && !player->get_right() && !player->get_left() && !player->get_jump()) {


					player->set_attack(true);
					player->throw_apple(render, renderer, "red_apple", "right", window_scale);
					player->reset_animation();

				}

			}

			if (e.key.keysym.sym == SDLK_e) {

				std::vector<std::tuple<SDL_Texture*, std::string>> dialogues;

				for (int i = 0; i < npcs.size(); i++) {

					if (npcs[i]->interact(player->get_dstrect(), dialogues)) {

						player->stop();

						game_state = 3;

						chatbox->load_texts(dialogues);
						chatbox->load_text();

					}

				}

			}

		}

		else if (game_state == 3) { // IF IN DIALOGUE 

			if (e.key.keysym.sym == SDLK_e) { // 'E' advances through dialogue 

				if (chatbox->get_finished()) {

					if (chatbox->get_dialogues_index() == chatbox->get_dialogues_length()) { // If at end of dialogues array (no more dialogues)

						game_state = 4; 
						chatbox->set_show(false);

					}

					else { // If there is more dialogue 

						chatbox->load_text();

					}

				}

				else { 

					chatbox->skip_dialogue(render, renderer);

				}

			}

		}

	}

	if (e.type == SDL_KEYUP) {

		if (game_state == 4) {

			if (e.key.keysym.sym == SDLK_d && !player->get_left()) {

				player->move_right(false);
				player->reset_animation();

			}

			else if (e.key.keysym.sym == SDLK_a && !player->get_right()) {


				player->move_left(false);
				player->reset_animation();

			}

			if (e.key.keysym.sym == SDLK_LSHIFT) {


				player->set_sprint(false);
				player->reset_animation();

			}

		}

	}
	 
}
