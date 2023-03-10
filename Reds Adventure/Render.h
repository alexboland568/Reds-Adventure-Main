#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

class Render
{

public:
	Render(double window_scale);
	~Render();

	SDL_Texture* load_image(std::string filepath, SDL_Renderer* renderer);
	SDL_Texture* load_text(std::string text, SDL_Color color, SDL_Renderer* renderer, int text_width);

	void font_size_conversion();

	void change_font_size(int size);

	TTF_Font* get_font();

private:

	TTF_Font* font = TTF_OpenFont("Res/Fonts/slkscrb.ttf", 20);

	double font_size;

};

#endif 