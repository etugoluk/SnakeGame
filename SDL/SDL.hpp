#ifndef SDL_HPP
#define SDL_HPP

#include <iostream>

#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"
#include "./SDL/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
#include "../inc/IGUI.hpp"

class SDL : public IGUI
{
	// int screensize;
	int blocksize;

	SDL_Window *window;
	SDL_Surface *surface;
	// SDL_Surface *info_block;
	SDL_Color color_text;

	SDL_Rect block;

	//text blocks
	SDL_Rect label;
	SDL_Rect level;
	SDL_Rect score;
	SDL_Rect change;
	SDL_Rect gui1;
	SDL_Rect gui2;
	SDL_Rect gui3;
	SDL_Rect usage;
	SDL_Rect arrow;

	TTF_Font* font;

public:
	SDL(Game &game);
	~SDL();

	void draw(Game &game, int color);
	void draw(Game &game) {std::cout << game.getLevel() << std::endl;}
	int execute(Game &game);

	// void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	void set_block(SDL_Surface *surface, int i, int j, Uint32 pixel);
};

#endif