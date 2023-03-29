#include "Inventory.h"

Inventory::Inventory(SDL_Renderer* renderer, Render* render, int window_width, int window_height, std::tuple<double, double> window_scale) {

	texture = render->load_image("Res/UI/inventory.png", renderer);
	dstrect.w = width * scale;
	dstrect.h = height * scale; 
	dstrect.x = window_width / 2 - dstrect.w / 2; 
	dstrect.y = window_height / 2 - dstrect.h / 2;

	hotbar_texture = render->load_image("Res/UI/hotbar.png", renderer);
	hotbar_dstrect.w = hotbar_width * scale;
	hotbar_dstrect.h = hotbar_height * scale;
	hotbar_dstrect.x = window_width / 2 - hotbar_dstrect.w / 2;
	hotbar_dstrect.y = window_height - hotbar_dstrect.h * 2;

	slot_width *= scale;
	slot_height *= scale;

	for (int i = 0; i < hotbar_size; i++) { // Hotbar in inventory 

		SDL_Rect rect = { dstrect.x + (14 * scale) + (i * (slot_width + (1 * scale))), dstrect.y + (103 * scale), slot_width, slot_height }; // y = 103 x = 14 
		hotbar_slots.push_back(new Items(i, rect));
		
	}

	for (int i = 0; i < hotbar_size; i++) { // Hotbar not in inventory 

		SDL_Rect rect = { hotbar_dstrect.x + (2 * scale) + (i * (slot_width + (1 * scale))), hotbar_dstrect.y, slot_width, slot_height };
		hotbar_slots.push_back(new Items(i, rect));

	}

	slots.push_back(hotbar_slots);

	int counter = 0;

	for (int i = 0; i < inventory_size / 3; i++) { // 4 Columns 

		for (int j = 0; j < inventory_size / 4;j++) { // 3 Rows 
			counter++;
			SDL_Rect rect = { dstrect.x + (14 * scale) + (i * (slot_width + (1 * scale))), dstrect.y + (47 * scale) + (j * (slot_height + (1 * scale))), slot_width, slot_height};

			inventory_slots.push_back(new Items((hotbar_slots.size() / 2) + counter, rect));

		}
		
	}

	slots.push_back(inventory_slots);

	for (int i = 0; i < equip_size; i++) {

		SDL_Rect rect = { dstrect.x + (22 * scale) + (i * (slot_width + (1 * scale))), dstrect.y + (25 * scale), slot_width, slot_height };

		equip_slots.push_back(new Items((hotbar_slots.size() / 2) + inventory_slots.size() + i, rect));

	}

	slots.push_back(equip_slots);

}

void Inventory::draw(SDL_Renderer* renderer, bool show) {

	if (show) {

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);

		for (int i = 0; i < slots.size(); i++) {

			for (int j = 0; j < slots[i].size(); j++) {

				SDL_SetTextureBlendMode(slots[i][j]->get_texture(), SDL_BLENDMODE_BLEND);
				if (slots[i][j]->get_selected())
					SDL_SetTextureAlphaMod(slots[i][j]->get_texture(), 128);
				else 
					SDL_SetTextureAlphaMod(slots[i][j]->get_texture(), 255);

				SDL_Rect rect = slots[i][j]->get_rect();
				SDL_RenderCopy(renderer, slots[i][j]->get_texture(), NULL, &rect);

			}

		}

	}

	else {

		SDL_RenderCopy(renderer, hotbar_texture, NULL, &hotbar_dstrect);

		for (int i = 0; i < slots[0].size() / 2; i++) {

			SDL_SetTextureBlendMode(slots[0][i + 4]->get_texture(), SDL_BLENDMODE_BLEND);
			if (slots[0][i + 4]->get_selected())
				SDL_SetTextureAlphaMod(slots[0][i + 4]->get_texture(), 128);
			else
				SDL_SetTextureAlphaMod(slots[0][i + 4]->get_texture(), 255);

			SDL_Rect rect = slots[0][i + 4]->get_rect();
			SDL_RenderCopy(renderer, slots[0][i + 4]->get_texture(), NULL, &rect);
			if (slots[0][i]->get_texture() != nullptr);// std::cout << "?" << std::endl;

		}


	}

}

int Inventory::get_current_slot() {
	
	return current_slot; 

}

void Inventory::set_current_slot(Items* item) {

	for (int i = 0; i < slots.size(); i++) {

		for (int j = 0; j < slots[i].size(); j++) {

			if (slots[i][j]->get_slot() == item->get_slot()) {

				slots[i][j] = item;
				slots[i][j]->set_empty(false);
				current_slot = item->get_slot();
				break; 

			}

		}

	}

	for (int i = 0; i < slots[0].size() / 2;i++) {

		slots[0][i + 4] = slots[0][i];
		slots[0][i + 4]->set_empty(false);

	}

}

void Inventory::update_inventory(bool show) {

	if (show) {

		for (int i = 0; i < slots[0].size() / 2; i++) {
			SDL_Rect rect = slots[0][i]->get_rect();
			std::cout << rect.x << ", " << rect.y << std::endl;
			//slots[0][i]->set_rect(slots[0][i + 4]->get_rect());

		}

	}

	else {

		for (int i = 0; i < slots[0].size() / 2; i++) {
			SDL_Rect rect = slots[0][i + 4]->get_rect();
			std::cout << rect.x << ", " << rect.y << std::endl; 
			//slots[0][i + 4]->set_rect(slots[0][i + 4]->get_rect());

		} 

	}

}

SDL_Rect Inventory::get_slot_rect(int slot, bool show) {

	for (int i = 0; i < slots.size(); i++) {

		for (int j = 0; j < slots[i].size(); j++) {

			if (slots[i][j]->get_slot() == slot) {

				return slots[i][j]->get_rect();

			}

		}

	}

	return {};

}

Inventory::~Inventory() {

	SDL_DestroyTexture(texture);

}