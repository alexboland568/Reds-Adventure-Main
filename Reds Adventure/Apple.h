#pragma once

#ifndef APPLE_H
#define APPLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>
#include <tuple>

#include "Camera.h"
#include "Render.h"

#include "Collision.h"

class Apple {
		
public:

	Apple(Render* render, SDL_Renderer* renderer, std::string name,std::string dir, SDL_Rect player_rect, std::tuple<double, double> window_scale);
	~Apple();

	void draw(SDL_Renderer* renderer, Camera* camera);

	void update();
	void move();
	void rotate();

private:

protected:

	std::string name; 

	SDL_Texture* texture;

	SDL_Rect dstrect, srcrect;

	int width, height;
	int src_w = 32, src_h = 32;
	int src_x, src_y;

	int vel, angle_inc;

	double angle;

	std::string dir;

};

#endif 