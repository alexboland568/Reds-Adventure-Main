#include "Apple.h"

Apple::Apple(Render* render, SDL_Renderer* renderer, std::string name, std::string dir, SDL_Rect player_rect, std::tuple<double, double> window_scale) {

	this->name = name;
	width = 16 * std::get<0>(window_scale);
	height = 16 * std::get<1>(window_scale);
	dstrect.w = width;
	dstrect.h = height;
	dstrect.x = player_rect.x;
	dstrect.y = player_rect.y; 

	srcrect = { 0, 0, src_w, src_h };

	angle = 0.0;
	vel = 4;
	angle_inc = 20.0;

	this->dir = dir;

	if (dir == "left") {

		vel *= -1; 
		angle_inc *= -1;

	}

	texture = render->load_image("Res/Apples/apples.png", renderer);

	if (name == "red_apple") {

		srcrect.x = 0;

	}

	else if (name == "green_apple") {

		srcrect.x = src_w;

	}

	else if (name == "blue_apple") {

		srcrect.x = src_w * 2;

	}

	else if (name == "purple_apple") {

		srcrect.x = src_w * 3;

	}

}

void Apple::draw(SDL_Renderer* renderer, Camera* camera) {

	SDL_Rect rect = camera->get_camera_dstrect(dstrect);

	SDL_RenderCopyEx(renderer, texture, &srcrect, &rect, angle, NULL, SDL_FLIP_NONE);

}

void Apple::update() {

	move();
	rotate();

}

void Apple::move() {

	dstrect.x += vel; 

}
void Apple::rotate() {

	angle += angle_inc; 

}

Apple::~Apple() {

	SDL_DestroyTexture(texture);

}