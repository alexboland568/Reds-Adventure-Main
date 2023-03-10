#include "Render.h"

Render::Render(double window_scale) {

	if (IMG_Init(IMG_INIT_PNG) < 0) {

		std::cout << "SDL_image couldn't initialize: " << IMG_GetError() << std::endl; 

	}

	if (TTF_Init() < 0) {

		std::cout << "SDL_ttf couldn't initialize: " << TTF_GetError() << std::endl;

	}

	font_size = 12;
	font_size_conversion();
	font_size *= window_scale;

	font = TTF_OpenFont("Res/Fonts/slkscrb.ttf", (int)font_size);

	if (font == NULL)
		std::cout << "Couldn't load font: " << TTF_GetError() << std::endl; 

}

SDL_Texture* Render::load_image(std::string filepath, SDL_Renderer* renderer) {

	SDL_Surface* surface = IMG_Load(filepath.c_str());

	if (surface == NULL)
		std::cout << "Couldn't load image: " << IMG_GetError() << std::endl; 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 

	return texture; 

}

SDL_Texture* Render::load_text(std::string text, SDL_Color color, SDL_Renderer* renderer, int text_width) {

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, text_width);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	return texture;

}

void Render::font_size_conversion() {

	double conversion = 4 / 3; // Points = 4/3px

	font_size = font_size * conversion;

}

void Render::change_font_size(int size) {

	font = TTF_OpenFont("Res/Fonts/slkscrb.ttf", size);

	if (font == NULL)
		std::cout << "Couldn't load font: " << TTF_GetError() << std::endl;

}

TTF_Font* Render::get_font() {

	return font; 
	
}

Render::~Render() {

	TTF_CloseFont(font);

	IMG_Quit();
	TTF_Quit();

}