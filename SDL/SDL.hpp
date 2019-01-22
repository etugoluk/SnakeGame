// #include <SDL2/SDL.h>
// # include "SDL_ttf.h"

#include <iostream>

#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"
#include "./SDL/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
#include "../inc/IGUI.hpp"

#define SCREENWIDTH 900
#define INFO_SIZE 300

class SDL : public IGUI
{
	// int screensize;
	int blocksize;

	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface *food;
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
	// SDL_Rect img;

	TTF_Font* font;

public:
	SDL(int);
	~SDL();

	void init(Game &game);
	void destroy();
	void draw(Game &game);
	void execute(Game &game);

	void set_pixel(SDL_Surface *surface, int i, int j, Uint32 pixel);
	// void scale_image(SDL_Surface *icon);
	// Uint32	get_pixel(SDL_Surface *sur, const int x, const int y);
};