#include "Engine.h"

Engine::Engine(std::string title, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

		std::cout << "SDL failed to initialize: " << SDL_GetError() << std::endl; 
		return; 

	}

	this->width = width;
	this->height = height; 

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0);

	if (this->window == NULL) {

		std::cout << "Window failed to initialize: " << SDL_GetError() << std::endl; 
		return; 

	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if (this->renderer == NULL) {

		std::cout << "Renderer failed to initialize: " << SDL_GetError() << std::endl; 
		return; 

	}

	SDL_SetRenderDrawColor(this->renderer, 100, 149, 237, 255);

}

void Engine::scale_window(int scale) {

	SDL_SetWindowSize(window, width * scale, height * scale);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	width = width * scale;
	height = height * scale; 

}

std::tuple<double, double> Engine::get_scale() {

	double default_width = 480;
	double default_height = 320;
	std::tuple<double, double> scaled_size = std::make_tuple(width / default_width, height / default_height);

	return scaled_size; 

}

void Engine::set_game_state(int state) {

	current_state = state; 

}

SDL_Renderer* Engine::get_renderer() {

	return renderer;

}

int Engine::get_width() {

	return width; 

}

int Engine::get_height() {

	return height; 

}

int Engine::get_game_state() {

	return current_state;

}

Engine::~Engine() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

}