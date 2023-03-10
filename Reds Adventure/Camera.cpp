#include "Camera.h"

Camera::Camera(SDL_Rect player, int window_width) {

	this->player_rect = player;
	this->window_width = window_width;

}

void Camera::update(bool in_scene, SDL_Rect player_rect, int window_width) {

	this->in_scene = in_scene;
	this->player_rect = player_rect;
	this->window_width = window_width;

}

SDL_Rect Camera::get_camera_dstrect(SDL_Rect rect) {

	int camera_x = rect.x - player_rect.x + window_width / 2 - player_rect.w / 2;

	SDL_Rect temp_rect;
	temp_rect = { camera_x, rect.y, rect.w, rect.h };

	if (!in_scene)
		return temp_rect;
	else
		return rect;

}

SDL_Rect Camera::get_player_rect() {

	return player_rect;

}

int Camera::get_window_width() {

	return window_width;

}