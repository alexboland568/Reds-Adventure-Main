#include "Chatbox.h"

Chatbox::Chatbox(Render* render, SDL_Renderer* renderer, int window_width, int window_height) {

	texture = render->load_image("Res/UI/chatbox.png", renderer);

	dstrect.w = window_width / 2; 
	dstrect.h = window_height * 0.3; 
	dstrect.x = window_width / 2 - dstrect.w / 2; 
	dstrect.y = window_height - ((double)dstrect.h * 1.2);

	chat_texture = NULL;
	chat_dstrect = {};

	frame_texture = render->load_image("Res/UI/icon_frame.png", renderer);
	frame_dstrect.w = dstrect.w * 0.30;
	frame_dstrect.h = (double)dstrect.h * 0.8;
	frame_dstrect.x = dstrect.x;
	frame_dstrect.y = dstrect.y - frame_dstrect.h;

	icon_dstrect.w = (double)frame_dstrect.w * 0.7; 
	icon_dstrect.h = (double)frame_dstrect.h * 0.7;
	icon_dstrect.x = frame_dstrect.x + frame_dstrect.w / 2 - icon_dstrect.w / 2 ;
	icon_dstrect.y = frame_dstrect.y + frame_dstrect.h / 2 - icon_dstrect.h / 2;

}

void Chatbox::update(Render* render, SDL_Renderer* renderer, int window_width, int window_height) {

	if (show && text_index < current_text.length() && !finished) {

		updating_text += current_text[text_index];

		chat_texture = render->load_text(updating_text, SDL_Color{ 0, 0, 0, 255 }, renderer, dstrect.w - border_spacing - 1);
		int texW = 0, texH = 0;
		SDL_QueryTexture(chat_texture, NULL, NULL, &texW, &texH);
		chat_dstrect.w = texW;
		chat_dstrect.h = texH;
		chat_dstrect.x = dstrect.x + border_spacing;
		chat_dstrect.y = dstrect.y + border_spacing;
		text_index += 1;

	}

	if (text_index == current_text.length() && !finished) {

		finished = true;

	}

}

void Chatbox::draw(SDL_Renderer* renderer) {

	if (show) {

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderCopy(renderer, chat_texture, NULL, &chat_dstrect);
		SDL_RenderCopy(renderer, frame_texture, NULL, &frame_dstrect);
		SDL_RenderCopy(renderer, icon_texture, NULL, &icon_dstrect);

	}

}

void Chatbox::load_texts(std::vector<std::tuple<SDL_Texture*, std::string>> dialogues) {

	this->show = true; 

	this->dialogues = dialogues; 

}

void Chatbox::load_text() {
	
	icon_texture = std::get<0>(dialogues[dialogues_index]);
	current_text = std::get<1>(dialogues[dialogues_index]);
	updating_text = "";
	text_index = 0;
	finished = false; 

	dialogues_index += 1;

}

void Chatbox::skip_dialogue(Render* render, SDL_Renderer* renderer) {

	updating_text = current_text; 

	chat_texture = render->load_text(updating_text, SDL_Color{ 0, 0, 0, 255 }, renderer, dstrect.w - border_spacing - 1);

	int texW = 0, texH = 0;
	SDL_QueryTexture(chat_texture, NULL, NULL, &texW, &texH);
	chat_dstrect.w = texW;
	chat_dstrect.h = texH;
	chat_dstrect.x = dstrect.x + border_spacing;
	chat_dstrect.y = dstrect.y + border_spacing;

	finished = true; 

}

bool Chatbox::get_show() {

	return show; 

}

void Chatbox::set_show(bool show) {

	this->show = show; 

	if (!show) {

		current_text = "";
		updating_text = "";
		text_index = 0;
		finished = false;
		dialogues_index = 0;

	}


}

bool Chatbox::get_finished() {

	return finished; 

}

int Chatbox::get_dialogues_index() {

	return dialogues_index;

}

int Chatbox::get_dialogues_length() {

	return dialogues.size();

}

Chatbox::~Chatbox() {

	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(chat_texture);

}