#include "NPC.h"

NPC::NPC(Render* render, SDL_Renderer* renderer, std::string name, std::tuple<double, double> window_scale) {

	this->name = name; 
	width = 32 * std::get<0>(window_scale);
	height = 32 * std::get<1>(window_scale);
	dstrect.w = width;
	dstrect.h = height; 

	srcrect = { 0, 0, src_w, src_h };
	
	vel = 3; 

	right = false;
	left = false; 
	face_right = true; 
	face_left = false; 

	sprite = NULL;
	icon = NULL; 

	animation = new Animation(src_w, src_h, 0, 4);

	chat_bubble_texture = render->load_image("Res/UI/chat_bubble.png", renderer);
	chat_bubble_rect = {};

}

bool NPC::collide(SDL_Rect player_rect) {

	Collision* collision = new Collision();

	if (collision->collide_rect(dstrect, player_rect)) {

		bubble = true; 

		return true; 

	}

	bubble = false; 

	return false; 

}

bool NPC::interact(SDL_Rect player_rect, std::vector<std::tuple<SDL_Texture*, std::string>>& dialogues) {

	Collision* collision = new Collision();

	if (collision->collide_rect(dstrect, player_rect)) {

		dialogues = this->dialogues;

		delete collision;

		if (dstrect.x > player_rect.x) {
			face_left = true;
			face_right = false; 
		}
		else {

			face_left = false;
			face_right = true; 

		}

		return true;

	}

	delete collision;

	return false;

}

void NPC::draw(SDL_Renderer* renderer, Camera* camera) {

	SDL_Rect rect = camera->get_camera_dstrect(dstrect);
	chat_bubble_rect.w = dstrect.w;
	chat_bubble_rect.h = dstrect.h / 2; 
	chat_bubble_rect.x = dstrect.x + dstrect.w / 2 - chat_bubble_rect.w / 2; 
	chat_bubble_rect.y = dstrect.y - chat_bubble_rect.h;
	SDL_Rect bubble_rect = camera->get_camera_dstrect(chat_bubble_rect);

	if (face_right) {

		SDL_RenderCopyEx(renderer, sprite, &srcrect, &rect, 0, NULL, SDL_FLIP_NONE);

	}

	else if (face_left) {

		SDL_RenderCopyEx(renderer, sprite, &srcrect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);

	}

	if (bubble) {

		SDL_RenderCopy(renderer, chat_bubble_texture, NULL, &bubble_rect);

	}

}

void NPC::update(SDL_Rect player_rect) {

	move();
	collide(player_rect);
	animate();

}

void NPC::move() {

	if (right)
		dstrect.x += vel;
	if (left)
		dstrect.x -= vel; 

}

void NPC::animate() {

	bool finished = false;
	srcrect = animation->update(finished);

}

void NPC::reset_animation() {

	srcrect.x = 0;
	animation->set_src_x(srcrect.x);

	if (right || left) { // MOVING 

		animation->animation_change(1, 4, 300);

	}

	else { // IDLE 

		animation->animation_change(0, 4, 500);

	}

	srcrect.y = animation->get_src_y();

}

void NPC::move_right(bool motion) {

	right = motion;
	if (right && !left) {
		face_right = true;
		face_left = false;
	}

}

void NPC::move_left(bool motion) {

	left = motion;
	if (left && !right) {
		face_right = false;
		face_left = true;
	}

}

std::string NPC::get_name() {

	return name; 

}

SDL_Rect NPC::get_dstrect() {

	return dstrect; 

}

bool NPC::get_right() {

	return right;

}

bool NPC::get_left() {

	return left; 

}

std::vector<std::tuple<SDL_Texture*, std::string>> NPC::get_dialogues() {

	return dialogues;

}

SDL_Texture* NPC::get_icon() {

	return icon; 

}

int NPC::get_vel() {

	return vel;

}

NPC::~NPC() {

	SDL_DestroyTexture(sprite);
	SDL_DestroyTexture(icon);

}