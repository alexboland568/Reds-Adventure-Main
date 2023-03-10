#pragma once

#ifndef NPC_H
#define NPC_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>
#include <string>
#include <tuple>

#include "Camera.h"
#include "Render.h"

#include "Collision.h"
#include "Animation.h"

class NPC
{

public:

	NPC(Render* render, SDL_Renderer* renderer, std::string name, std::tuple<double, double> window_scale);
	~NPC();

	virtual void initialize(Render* render, SDL_Renderer* renderer, std::tuple<double, double> window_scale, SDL_Texture* player_icon) = 0;

	void draw(SDL_Renderer* renderer, Camera* camera);
	bool collide(SDL_Rect player_rect);
	bool interact(SDL_Rect player_rect, std::vector<std::tuple<SDL_Texture*, std::string>>& dialogues);
	void update(SDL_Rect player_rect);
	void move();
	void animate();

	void move_right(bool motion);
	void move_left(bool motion);

	void reset_animation();

	std::string get_name();

	SDL_Rect get_dstrect();

	bool get_right();
	bool get_left();

	std::vector<std::tuple<SDL_Texture*, std::string>> get_dialogues();

	SDL_Texture* get_icon();

	int get_vel();

protected:

	std::string name; 

	SDL_Texture* sprite;
	SDL_Texture* icon; 

	SDL_Texture* chat_bubble_texture;
	SDL_Rect chat_bubble_rect;

	SDL_Rect dstrect, srcrect; 

	int width, height; 
	int src_w = 32, src_h = 32; 
	int src_x, src_y;

	int vel;

	bool right, left;
	bool face_right, face_left; 

	bool bubble = false; // chat_bubble if player is in range 

	std::vector<std::tuple<SDL_Texture*, std::string>> dialogues; // Contains icon and text  

	Animation* animation;

};

#endif 