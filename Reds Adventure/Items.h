#ifndef ITEMS_H
#define ITEMS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Render.h"

#include <string>

class Items {

public:

	Items(int slot, SDL_Rect rect);
	Items(SDL_Renderer* renderer, Render* render, std::string name, int buying_cost, int selling_cost, int ms, int armor, int health, int attack, int item_type, int slot, int id, SDL_Rect rect);
	~Items();

	std::string get_name();

	int get_buying_cost(), get_selling_cost();

	int get_id();

	int get_ms();
	int get_armor();
	int get_health();
	int get_attack();

	int get_item_type();

	SDL_Texture* get_texture();
	SDL_Rect get_rect();
	void set_rect(SDL_Rect);

	int get_slot();
	void set_slot(int slot);

	void set_empty(bool empty);

	bool get_selected();
	void set_selected(bool selected);

protected:

	std::string name; 
	
	int buying_cost, selling_cost; 

	int id;

	// Stats if applicable 
	int ms; // Movement speed 
	int armor;
	int health;
	int attack;

	int item_type;

	SDL_Texture* texture;
	SDL_Rect dstrect;

	int slot;

	bool selected = false; 

	bool empty = true;



};

#endif 