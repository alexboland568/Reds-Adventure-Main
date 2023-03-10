#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL/SDL.h>

class Animation
{

public:

	Animation(int src_w, int src_h, int row, int cols);

	void animation_change(int row, int cols, int delay);

	SDL_Rect update(bool &finished);

	void set_src_x(int src_x);

	int get_src_y();

private:

	int src_w, src_h, cols;

	int src_x = 0, src_y;

	int delay = 500; // Delay in ms
	int counter = 0;

};

#endif 