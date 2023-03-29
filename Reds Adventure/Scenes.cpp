#include "Scenes.h"

Scenes::Scenes(Render* render, SDL_Renderer* renderer, int window_width, int window_height) {

	this->window_width = window_width;
	this->window_height = window_height;

	counter = 0;
	transition_color = { 0, 0, 0, 255 };
	transition_alpha = 255;
	delay = 1000;
	transition_texture = render->load_image("Res/Scenes/transition.png", renderer);
	// SDL_SetRenderDrawColor(this->renderer, 100, 149, 237, 255)
	//SDL_Texture* red_icon = render->load_image("Res/Characters/Red/icon.png", renderer);

	// Scene 1 (Red and Grandpa)

	/*dialogues.push_back("What did I tell you about crying?");
	icons.push_back(red_icon);
	dialogues.push_back("Ive raised you to not be a coward.");
	icons.push_back(red_icon);
	dialogues.push_back("Im sorry grandpa but I hurt myself.");
	icons.push_back(red_icon);
	dialogues.push_back("Do you think youll be able to find your father the way you are now?");
	icons.push_back(red_icon);
	dialogues.push_back("Sorry Grandpa. Ill do better.");
	icons.push_back(red_icon);
	dialogues.push_back("Dont apologize. Get up and lets go.");
	icons.push_back(red_icon);
	dialogues.push_back("The ceremony for your mythic starts soon. Dont be late. Be sure to check on your mother first.");
	icons.push_back(red_icon);

	all_dialogues.push_back(dialogues);*/

}

void Scenes::draw(SDL_Renderer* renderer) {

	if (scene_index == 0) {

		SDL_SetTextureBlendMode(transition_texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(transition_texture, transition_alpha);

		SDL_RenderCopy(renderer, transition_texture, NULL, NULL);

	}

}

void Scenes::scene_1(SDL_Renderer* renderer, Chatbox* chatbox, Player* player, NPC* grandpa, int& game_state) {

	in_scene = true; 

	if (!player->get_sleeping() && scene_part == 0) {

		game_state = 2;
		player->set_sleeping(true);
		player->reset_animation();

	}

	if (counter >= (delay / 30)) {

		if (transition_alpha > 0)
			transition_alpha -= 1;

	}

	if (transition_alpha > 0)
		counter++;
	else {

		if (grandpa->get_dstrect().x > player->get_dstrect().x + player->get_dstrect().w && !grandpa->get_left() && scene_part == 0) {

			game_state = 2;
			grandpa->move_left(true);
			grandpa->reset_animation();
			scene_part += 1;

		}

		else if (grandpa->get_dstrect().x <= player->get_dstrect().x + player->get_dstrect().w && grandpa->get_left() && scene_part == 1) {

			grandpa->move_left(false);

			grandpa->reset_animation();

			player->set_sleeping(false);
			player->reset_animation();

			game_state = 3;

			chatbox->load_texts(grandpa->get_dialogues());
			chatbox->load_text();

			scene_part += 1;

		}

		if (chatbox->get_dialogues_index() == chatbox->get_dialogues_length() && scene_part == 2) { // If at end of dialogues array (no more dialogues)

			game_state = 2;
			chatbox->set_show(false);

			grandpa->move_right(true);
			grandpa->reset_animation();

			scene_part += 1;

		}

		if (grandpa->get_dstrect().x > window_width && scene_part == 3) {

			game_state = 4; 

			grandpa->move_right(false);
			grandpa->reset_animation();

			scene_part += 1;

			in_scene = false; 

			scene_index += 1;

		}
	}

}

bool Scenes::get_in_scene() {

	return in_scene;

}