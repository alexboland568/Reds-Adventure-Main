// Engine Setup
#include "Engine.h"
#include "Camera.h"
#include "Input.h"
#include "Render.h"
#include "Scenes.h"

// Objects
#include "Clouds.h"

// Characters
#include "Player.h"
#include "Grandpa.h"

// UI
#include "Chatbox.h"

// Inventory/Items
#include "Inventory.h"
#include "Tattered_Boots.h"

int main(int argc, char** argv) {

	srand(time(NULL));

	Engine* engine = new Engine("Red's Adventure", 480, 320);
	//engine->scale_window(3);
	Input* input = new Input();
	Render* render = new Render(std::get<1>(engine->get_scale()));
	Scenes* scenes = new Scenes(render, engine->get_renderer(), engine->get_width(), engine->get_height());

	Chatbox* chatbox = new Chatbox(render, engine->get_renderer(), engine->get_width(), engine->get_height());

	std::vector<Clouds*> clouds;
	for (int i = 0; i < 20; i++)
		clouds.push_back(new Clouds(engine->get_width(), engine->get_height(), engine->get_scale()));
	for (int i = 0; i < 20; i++)
		clouds[i]->generate(render, engine->get_renderer());

	Player* player = new Player(engine->get_renderer(), render, engine->get_scale());
	Camera* camera = new Camera(player->get_dstrect(), engine->get_width());

	Inventory* inventory = new Inventory(engine->get_renderer(), render, engine->get_width(), engine->get_height(), engine->get_scale());

	std::vector<NPC*> npcs;
	NPC* grandpa = new Grandpa(render, engine->get_renderer(), "Grandpa", engine->get_scale());
	npcs.push_back(grandpa);
	for (int i = 0; i < npcs.size(); i++)
		npcs[i]->initialize(render, engine->get_renderer(), engine->get_scale(), player->get_icon_texture());
	
	bool running = true;

	const int FPS = 30; 
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	std::tuple<int, int> bounds = std::make_tuple(0, 3000);

	Tattered_Boots* tattered_boots = new Tattered_Boots(engine->get_renderer(), render, "Tattered Boots", 5, 2, 2, 0, 0, 0, inventory->BOOTS, 0, 1, inventory->get_slot_rect(0, !player->get_in_inventory()));
	inventory->set_current_slot(tattered_boots);
	//inventory->update_inventory(player->get_in_inventory());

	while (running) {

		frameStart = SDL_GetTicks();

		int game_state = engine->get_game_state();
		if (scenes->get_in_scene()) {

			scenes->scene_1(engine->get_renderer(), chatbox, player, grandpa, game_state);

		}

		camera->update(scenes->get_in_scene(), player->get_dstrect(), engine->get_width());
		input->update(running, render, engine->get_renderer(), player, inventory, chatbox, npcs, game_state, engine->get_scale());
		
		engine->set_game_state(game_state);

		for (int i = 0; i < clouds.size(); i++) {

			clouds[i]->update(render, engine->get_renderer());

		}

		player->update();
		for (int i = 0; i < npcs.size(); i++)
			npcs[i]->update(player->get_dstrect());
		chatbox->update(render, engine->get_renderer(), engine->get_width(), engine->get_height());

		SDL_RenderClear(engine->get_renderer());

		// Draw Here

		

		for (int i = 0; i < clouds.size(); i++) {

			clouds[i]->draw(engine->get_renderer());

		}

		for (int i = 0; i < npcs.size(); i++)
			npcs[i]->draw(engine->get_renderer(), camera);

		player->draw(engine->get_renderer(), camera, bounds);
		
		for (int i = 0; i < player->get_apples().size(); i++) {

			player->get_apples()[i]->draw(engine->get_renderer(), camera);
			player->get_apples()[i]->update();

		}

		chatbox->draw(engine->get_renderer());

		//inventory->draw(engine->get_renderer(), player->get_in_inventory());

		if (scenes->get_in_scene()) {

			scenes->draw(engine->get_renderer());

		}

		
		SDL_RenderPresent(engine->get_renderer());

		// End Draw


		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {

			SDL_Delay(frameDelay - frameTime);

		}

	}
	
	// Clean up resources 
	delete chatbox; 
	delete inventory;

	delete grandpa;
	delete player;

	delete scenes; 
	delete render; 
	delete input; 
	delete camera;
	delete engine; 

	return 0;

}