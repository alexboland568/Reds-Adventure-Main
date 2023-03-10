#include "Clouds.h"

Clouds::Clouds(int window_width, int window_height, std::tuple<double, double> window_scale) {

	this->texture = NULL;
	this->dstrect.w = 64 * std::get<0>(window_scale);
	this->dstrect.h = 32 * std::get<1>(window_scale);
	this->window_width = window_width;
	this->window_height = window_height; 
	this->vel = 0;

}

void Clouds::generate(Render* render, SDL_Renderer* renderer) {

	int cloud_selection = (rand() % (7 - 1 + 1)) + 1;

	dstrect.y = (rand() % ((window_height / 4) - 0 + 1)) + 1;
	dstrect.x = (rand() % (window_width - 0 + 1)) + 0;

	int vel_sign = (rand() % (1 - 0 + 1)) + 0; // 0 == Positive 1 == Negative
	
	vel = (rand() % (2 - 1 + 1)) + 1;

	if (vel_sign == 1)
		vel *= -1;

	std::string cloud_file = "Res/Objects/Clouds/cloud" + std::to_string(cloud_selection) + ".png";

	texture = render->load_image(cloud_file, renderer);

}

void Clouds::regenerate(Render* render, SDL_Renderer* renderer, int pos) {

	int cloud_selection = (rand() % (7 - 1 + 1)) + 1;

	dstrect.y = (rand() % ((window_height / 4) - 0 + 1)) + 1;
	
	int vel_sign = 0; 
	if (pos == 0) {
		dstrect.x = -dstrect.w;
		vel_sign = 1;
	}
	else if (pos == 1) {
		dstrect.x = window_width;
		vel_sign = -1;
	}

	vel = vel_sign;

	std::string cloud_file = "Res/Objects/Clouds/cloud" + std::to_string(cloud_selection) + ".png";

	texture = render->load_image(cloud_file, renderer);

}

void Clouds::draw(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, texture, NULL, &dstrect);

}

void Clouds::update(Render* render, SDL_Renderer* renderer) {

	dstrect.x += vel;

	if (dstrect.x > window_width) {

		regenerate(render, renderer, 0); // 0 = Spawn left, 1 = Spawn right 

	}

	else if (dstrect.x + dstrect.w < 0) {

		regenerate(render, renderer, 1);

	}

}

Clouds::~Clouds() {

	SDL_DestroyTexture(texture);

}