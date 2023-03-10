#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>

#include <iostream>
#include <string>
#include <tuple>

class Engine
{

public:

	Engine(std::string title, int width, int height);
	~Engine();
	
	void scale_window(int scale);

	std::tuple<double, double> get_scale();

	void set_game_state(int state);

	SDL_Renderer* get_renderer();

	int get_width(), get_height();
	
	int get_game_state();

private:

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr; 

	int width = 0, height = 0; 

	enum GAME_STATE {MENU = 0, PAUSE = 1, SCENE = 2, DIALOGUE = 3, PLAYING = 4};
	int current_state = 4;

};

#endif 