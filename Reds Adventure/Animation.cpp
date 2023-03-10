#include "Animation.h"

Animation::Animation(int src_w, int src_h, int row, int cols) {

	this->src_w = src_w;
	this->src_h = src_h; 
	this->src_y = row; 
	this->cols = cols; 

}

void Animation::animation_change(int row, int cols, int delay) {

	this->src_y = row * src_h;
	
	this->cols = cols; 

	this->delay = delay;

	counter = 0;

}

SDL_Rect Animation::update(bool& finished) {

	SDL_Rect srcrect = { this->src_x, this->src_y, this->src_w, this->src_h };

	int texture_width = cols * this->src_w;

	if (counter >= (delay / 30)) { // delay / FPS 

		this->src_x += this->src_w;

		if (this->src_x >= texture_width) {

			this->src_x = 0;

			finished = true; 

		}

		counter = 0;

	}

	counter++;

	return srcrect; 

}

void Animation::set_src_x(int src_x) {

	this->src_x = src_x; 

}

int Animation::get_src_y() {

	return src_y;

}