#pragma once

#ifndef GRANDPA_H
#define GRANDPA_H

#include "NPC.h"

class Grandpa : public NPC 
{

public:

	Grandpa(Render* render, SDL_Renderer* renderer, std::string name, std::tuple<double, double> window_scale) : NPC(render, renderer, name, window_scale) {}

private:

	void initialize(Render* render, SDL_Renderer* renderer, std::tuple<double, double> window_scale, SDL_Texture* player_icon) {

		sprite = render->load_image("Res/Characters/Grandpa/animations.png", renderer);
		dstrect.x = 512 * std::get<0>(window_scale);
		dstrect.y = 200 * std::get<1>(window_scale);

		icon = render->load_image("Res/Characters/Grandpa/icon.png", renderer);

		vel = 2;

		face_right = false;
		face_left = true; 

		// Scene 1 Text 
		dialogues.push_back(std::make_tuple(icon, "What did I tell you about crying?"));
		dialogues.push_back(std::make_tuple(icon, "Ive raised you to not be a coward."));
		dialogues.push_back(std::make_tuple(player_icon, "Im sorry grandpa but I hurt myself."));
		dialogues.push_back(std::make_tuple(icon, "Do you think youll be able to find your father the way you are now?"));
		dialogues.push_back(std::make_tuple(player_icon, "Sorry Grandpa. Ill do better."));
		dialogues.push_back(std::make_tuple(icon, "Dont apologize. Get up and lets go."));
		dialogues.push_back(std::make_tuple(icon, "The ceremony for your mythic starts soon. Dont be late. Be sure to check on your mother first."));

	}

};

#endif 