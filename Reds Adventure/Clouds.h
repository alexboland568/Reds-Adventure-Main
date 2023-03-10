#ifndef CLOUDS_H
#define CLOUDS_H

#include <string>
#include <tuple>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Render.h"

class Clouds {

public:

	Clouds(int window_width, int window_height, std::tuple<double, double> window_scale);
	~Clouds();

	void generate(Render* render, SDL_Renderer* renderer);
	void regenerate(Render* render, SDL_Renderer* renderer, int pos);
	void draw(SDL_Renderer* renderer);
	void update(Render* render, SDL_Renderer* renderer);

private:

	SDL_Texture* texture;

	SDL_Rect dstrect; 

	int window_width, window_height;

	int vel;

};

#endif 