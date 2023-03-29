#include "Items.h"

Items::Items(int slot, SDL_Rect rect) {

	name = "";
	buying_cost = 0;
	selling_cost = 0;
	id = 0;
	ms = 0;
	armor = 0;
	health = 0;
	attack = 0;
	item_type = 0; 
	texture = nullptr; 
	this->slot = slot; 
	selected = false;

	dstrect = rect;

}

Items::Items(SDL_Renderer* renderer, Render* render, std::string name, int buying_cost, int selling_cost, int ms, int armor, int health, int attack, int item_type, int slot, int id, SDL_Rect rect) {

	this->name = name;
	this->buying_cost = buying_cost;
	this->selling_cost = selling_cost;
	this->id = id;

	this->ms = ms; 
	this->armor = armor; 
	this->health = health;
	this->attack = attack;

	this->item_type = item_type; 

	this->texture = nullptr;

	this->slot = slot; 

	selected = false; 

	this->dstrect = rect;

}

std::string Items::get_name() {

	return name; 

}

int Items::get_buying_cost() {

	return buying_cost;

}

int Items::get_selling_cost() {

	return selling_cost; 

}

int Items::get_id() {

	return id; 

}

int Items::get_ms() {

	return ms; 

}

int Items::get_armor() {

	return armor; 

}

int Items::get_health() {

	return health; 

}

int Items::get_attack() {

	return attack; 

}

int Items::get_item_type() {

	return item_type; 

}

SDL_Texture* Items::get_texture() {

	return texture; 

}

SDL_Rect Items::get_rect() {

	return dstrect;

}

int Items::get_slot() {

	return slot; 

}

void Items::set_slot(int slot) {

	this->slot = slot; 

}

void Items::set_rect(SDL_Rect rect) {

	this->dstrect = rect;

}

void Items::set_empty(bool empty) {
	
	this->empty = empty;

}

bool Items::get_selected() {
	
	return selected;

}

void Items::set_selected(bool selected) {

	this->selected = selected;

}

Items::~Items() {

	SDL_DestroyTexture(texture);

}