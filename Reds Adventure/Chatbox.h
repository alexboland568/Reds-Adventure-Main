#pragma once

#ifndef CHATBOX_H
#define CHATBOX_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <vector>
#include <tuple>

#include "Render.h"

class Chatbox
{

public:

	Chatbox(Render* render, SDL_Renderer* renderer, int window_width, int window_height);
	~Chatbox();

	void draw(SDL_Renderer* renderer);
	void update(Render* render, SDL_Renderer* renderer, int window_width, int window_height);

	void load_texts(std::vector<std::tuple<SDL_Texture*, std::string>> dialogues); // Loads all of NPCs dialogue
	void load_text(); // Loads the dialogue one by one starting from the first one 
	void skip_dialogue(Render* render, SDL_Renderer* renderer); // Speed up the dialogue 

	bool get_show();
	void set_show(bool show);

	bool get_finished();
	int get_dialogues_index();
	int get_dialogues_length();

private:

	SDL_Texture* texture; 
	SDL_Texture* chat_texture; 
	SDL_Texture* frame_texture;
	SDL_Texture* icon_texture;

	SDL_Rect dstrect; 
	SDL_Rect chat_dstrect; 
	SDL_Rect frame_dstrect;
	SDL_Rect icon_dstrect;

	bool show = false; 

	std::vector<std::tuple<SDL_Texture*, std::string>> dialogues;

	std::string current_text = "";
	std::string updating_text = "";
	int dialogues_index = 0;
	int text_index = 0;

	int border_spacing = 20;

	bool finished = false; 

};

#endif 