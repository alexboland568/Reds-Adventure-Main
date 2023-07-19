#include "Bird.h"

Bird::Bird(int x, int y, int window_scale, SDL_Renderer* renderer, Render* render) {

	dstrect = { x * window_scale, y * window_scale, 32 * window_scale, 32 * window_scale };

	texture = render->load_image("Res/Animals/bird-flying.png", renderer);

	right = false;
	left = false; 

	vel = 2;

}

void Bird::update() {

	animate();
	move();

}

void Bird::move() {

	if (right)
		dstrect.x += vel;
	else if (left)
		dstrect.y -= vel; 

}

void Bird::draw(SDL_Renderer* renderer) {

	if (right)
		SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, 0, NULL, SDL_FLIP_NONE);
	else if (left) 
		SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, 0, NULL, SDL_FLIP_HORIZONTAL);

}

void Bird::animate() {

	bool finished = false; 

	srcrect = animation->update(finished);

}

Bird::~Bird() {

	SDL_DestroyTexture(texture);

}