#include "Player.h"

Player::Player(SDL_Renderer* renderer, Render* render, std::tuple<double, double> window_scale) {

	texture = render->load_image("Res/Characters/Red/animations.png", renderer);
	icon = render->load_image("Res/Characters/Red/icon.png", renderer);

	width = 32 * std::get<0>(window_scale);
	height = 32 * std::get<1>(window_scale);

	dstrect.x = 100 * std::get<0>(window_scale);
	dstrect.y = 200 * std::get<1>(window_scale);
	dstrect.w = width;
	dstrect.h = height;

	srcrect = { 0, 0, src_w, src_h };

	vel_x = 3 * std::get<0>(window_scale);
	sprint_vel = vel_x * 2;
	default_jump_vel = 6;
	jump_vel = default_jump_vel;

	health = 20;
	max_health = 20;
	ms = 0;
	armor = 0; 
	attackStat = 1;

	in_inventory = false; 

	animation = new Animation(src_w, src_h, 0, 4);

}


void Player::draw(SDL_Renderer* renderer, Camera* camera, std::tuple<int, int> map_bounds) {

	SDL_Rect rect = camera->get_camera_dstrect(dstrect, map_bounds);

	if (face_right) {

		SDL_RenderCopyEx(renderer, texture, &srcrect, &rect, 0, NULL, SDL_FLIP_NONE);

	}

	else if (face_left) {

		SDL_RenderCopyEx(renderer, texture, &srcrect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);

	}

	//std::cout << "(" << dstrect.x << ", " << dstrect.y << ")" << std::endl; 

}

void Player::update() {

	animate();

	move();

}

void Player::move() {

	if (right) {

		if (sprint)
			dstrect.x += sprint_vel;
		else
			dstrect.x += vel_x; 

	}

	else if (left) {

		if (sprint)
			dstrect.x -= sprint_vel;
		else
			dstrect.x -= vel_x; 

	}

	if (dstrect.x <= 0) {

		dstrect.x = 0;

	}

	jumping();

}

void Player::interact() {

	

}

void Player::jumping() {

	if (jump) {

		dstrect.y -= jump_vel;
		jump_vel -= gravity; 

		if (jump_vel < (default_jump_vel + gravity) * - 1) {
		
			jump = false; 
			jump_vel = default_jump_vel;
			
			reset_animation();

		}

	}

}

void Player::throw_apple(Render* render, SDL_Renderer* renderer, std::string name, std::string dir, std::tuple<double, double> window_scale) {

	apples.push_back(new Apple(render, renderer, name, dir, dstrect, window_scale));

}

void Player::animate() {
	
	bool finished = false; 
	srcrect = animation->update(finished);

	if (finished && attack) {
		attack = false;
		reset_animation();
	}

}

void Player::move_right(bool motion) {

	right = motion; 
	if (right && !left) {
		face_right = true;
		face_left = false; 
	}

}

void Player::move_left(bool motion) {

	left = motion;
	if (left && !right) {
		face_right = false;
		face_left = true; 
	}

}

void Player::set_sprint(bool sprint) {

	this->sprint = sprint; 

}

void Player::set_jump(bool jump) {

	this->jump = jump; 

}

void Player::set_attack(bool attack) {

	this->attack = attack; 

}

void Player::set_sleeping(bool sleeping) {

	this->sleeping = sleeping; 

}

void Player::reset_animation() {

	this->srcrect.x = 0;
	animation->set_src_x(this->srcrect.x);

	if (right || left) { // MOVING 

		if (!jump && !attack && !sprint) // If moving right or left walking  
			animation->animation_change(1, 4, 300);
		else if (!jump && !attack && sprint) // If sprinting right or left 
			animation->animation_change(2, 4, 200);
		else if (jump && !attack && !sprint) // If jumping 
			animation->animation_change(4, 5, 400);

	}

	else { // IDLE 

		if (!jump && !attack && !sleeping) // If standing in place 
			animation->animation_change(0, 4, 500);
		else if (jump && !attack && !sleeping) // If jumping in place
			animation->animation_change(4, 5, 200);
		else if (!jump && attack) // If attacking 
			animation->animation_change(5, 2, 300);
		else if (sleeping) // If sleeping 
			animation->animation_change(3, 6, 500);

	}

	srcrect.y = animation->get_src_y();

}


void Player::stop() { // Stops the player's current movement 

	right = false;
	left = false; 

	attack = false; 

	reset_animation();

}

int Player::get_width() {

	return width;

}

int Player::get_height() {

	return height; 

}

int Player::get_src_w()
{
	return src_w;

}

int Player::get_src_h() {

	return src_h;

}
SDL_Rect Player::get_dstrect() {

	return dstrect; 

}

bool Player::get_face_right() {

	return face_right; 

}

bool Player::get_face_left() {

	return face_left; 

}

bool Player::get_right() {

	return right; 

}

bool Player::get_left() {

	return left; 

}

bool Player::get_jump() {

	return jump;

}

bool Player::get_attack() {

	return attack; 

}

bool Player::get_sleeping() {

	return sleeping; 

}

bool Player::get_sprint() {
	
	return sprint; 

}

int Player::get_health() {

	return health; 

}

int Player::get_max_health() {

	return max_health; 

}

int Player::get_ms() {

	return ms; 

}

int Player::get_armor() {

	return armor; 

}

int Player::get_attackStat() {

	return attackStat; 

}

bool Player::get_in_inventory() {

	return in_inventory;

}

void Player::set_in_inventory(bool show) {

	in_inventory = show;

}

Animation* Player::get_animation() {

	return animation;

}

std::vector<std::string> Player::get_dialogues() {

	return dialogues; 

}

SDL_Texture* Player::get_icon_texture() {

	return icon;

}

std::vector<Apple*> Player::get_apples() {

	return apples;

}

Player::~Player() {

	delete animation;

	SDL_DestroyTexture(texture);

}