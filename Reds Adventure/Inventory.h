#ifndef INVENTORY_H
#define INVENTORY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>
#include <vector>
#include <tuple>

#include "Render.h"

#include "Items.h"

class Inventory {

public:

	Inventory(SDL_Renderer* renderer, Render* render, int window_width, int window_height, std::tuple<double, double> window_scale);
	~Inventory();

	void draw(SDL_Renderer* renderer, bool show);

	int get_current_slot();
	void set_current_slot(Items* item);

	enum ITEM_TYPE { NONE = 0, WEAPON = 1, ARMOR = 2, BOOTS = 3 };

	void update_inventory(bool show);

	SDL_Rect get_slot_rect(int slot, bool show);
	//void set_slot_rect()



private:

	std::vector<Items*> hotbar_slots; // Hotbar in inventory
	std::vector<Items*> inventory_slots;
	std::vector<Items*> equip_slots;
	std::vector<std::vector<Items*>> slots; 

	std::vector<SDL_Rect> dstrects;

	int inventory_size = 12;
	int hotbar_size = 4;
	int equip_size = 3; // Helmet, chestplate, boots 

	int current_slot = 0;

	SDL_Texture* texture;
	SDL_Texture* hotbar_texture;
	SDL_Rect dstrect;
	SDL_Rect hotbar_dstrect;

	int width = 96;
	int height = 128;
	int hotbar_width = 73;
	int hotbar_height = 20;

	int slot_width = 17;
	int slot_height = 17;

	double scale = 1.0;

};

#endif 