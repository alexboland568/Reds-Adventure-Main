#pragma once

#ifndef BIRD_H
#define BIRD_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Render.h"

#include "Animation.h"

class Bird {

public:

	Bird(int x, int y, int window_scale, SDL_Renderer* renderer, Render* render);
	~Bird();

	void update();
	void move();
	void draw(SDL_Renderer* renderer);
	void animate();

	SDL_Rect get_dstrect();

private:

	Animation* animation;

	SDL_Texture* texture; 

	SDL_Rect dstrect, srcrect;

	bool right, left;

	int vel; 

};

#endif 