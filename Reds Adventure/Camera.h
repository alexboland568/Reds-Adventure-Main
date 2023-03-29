#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL/SDL.h>

#include <iostream>
#include <tuple>

class Camera
{

public:

	Camera(SDL_Rect player, int window_width);

	void update(bool in_scene, SDL_Rect player_rect, int window_width);

	SDL_Rect get_camera_dstrect(SDL_Rect rect);
	SDL_Rect get_camera_dstrect(SDL_Rect rect, std::tuple<int, int> bounds);

	SDL_Rect get_player_rect();
	int get_window_width();

private:

	bool in_scene;
	SDL_Rect player_rect;
	int window_width;

};

#endif 