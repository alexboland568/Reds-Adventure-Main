#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <SDL/SDL.h>

#include <tuple>
#include <functional>

#include "Player.h"
#include "Inventory.h"
#include "NPC.h"
#include "Chatbox.h"

class Input
{

public:

	void update(bool& running, Render* render, SDL_Renderer* renderer, Player* player, Inventory* inventory, Chatbox* chatbox, std::vector<NPC*> npcs, int& game_state, std::tuple<int, int> window_scale);

private:

	SDL_Event e;

};

#endif 