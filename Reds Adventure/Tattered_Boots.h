#ifndef TATTERED_BOOTS_H
#define TATTERED_BOOTS_H

#include "Items.h"

class Tattered_Boots : public Items {

public:

	Tattered_Boots(SDL_Renderer* renderer, Render* render, std::string name, int buying_cost, int selling_cost, int ms, int armor, int health, int attack, int item_type, int slot, int id, SDL_Rect rect) : Items(renderer, render, name, buying_cost, selling_cost, ms, armor, health, attack, item_type, slot, id, rect) {
	
		this->texture = render->load_image("Res/Items/Armor/tattered_boots.png", renderer);

	}

private:

};

#endif 