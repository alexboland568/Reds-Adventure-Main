#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "Camera.h"
#include "Render.h"

#include "Animation.h"

#include "Collision.h"

#include "Apple.h"

class Player
{

public:

	Player(SDL_Renderer* renderer, Render* render, std::tuple<double, double> window_scale);
	~Player();

	//void load_dialogues();

	void update();
	void move();
	void interact();
	void jumping();
	void animate();
	void draw(SDL_Renderer* renderer, Camera* camera, std::tuple<int, int> map_bounds);

	void throw_apple(Render* render, SDL_Renderer* renderer, std::string name, std::string dir, std::tuple<double, double> window_scale);

	void move_right(bool motion);
	void move_left(bool motion);
	void set_sprint(bool sprint);
	void set_jump(bool jump);
	void set_attack(bool attack);
	void set_sleeping(bool sleeping);

	void reset_animation();

	void stop();

	SDL_Rect get_dstrect();

	int get_width();
	int get_height();
	int get_src_w();
	int get_src_h();

	bool get_right();
	bool get_left();

	bool get_jump();
	bool get_attack();

	bool get_sprint();

	bool get_sleeping();

	Animation* get_animation();

	std::vector<std::string> get_dialogues();

	SDL_Texture* get_icon_texture();

	std::vector<Apple*> get_apples();

private:

	Animation* animation;

	SDL_Texture* texture;
	SDL_Texture* icon;

	SDL_Rect dstrect, srcrect;

	int vel_x, sprint_vel;
	double jump_vel, default_jump_vel;

	int width, height;
	int src_w = 32, src_h = 32;
	double gravity = 0.5;

	bool jump = false; 
	bool sprint = false; 

	bool right = false, left = false; 
	bool face_right = true;
	bool face_left = false;

	bool attack = false; 

	bool sleeping = false; 

	std::vector<std::string> dialogues; 

	std::vector<Apple*> apples;

};

#endif 