#pragma once

#ifndef SCENES_H
#define SCENES_H

#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Render.h"
#include "Chatbox.h"

#include "Player.h"
#include "NPC.h"

class Scenes
{

public:

	Scenes(Render* render, SDL_Renderer* renderer, int window_width, int window_height);

	void draw(SDL_Renderer* renderer);

	void scene_1(SDL_Renderer* renderer, Chatbox* chatbox, Player* player, NPC* grandpa, int& game_state);

	bool get_in_scene();

private:

	int window_width, window_height;

	int scene_index = 0; // 0 = Scene 1 
	int scene_part = 0; // 0 = First part of scene

	bool in_scene = true;

	int counter;
	SDL_Color transition_color;
	int transition_alpha;
	int delay;

	SDL_Texture* transition_texture;


};

#endif 