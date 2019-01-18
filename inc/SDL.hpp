#include <SDL2/SDL.h>
# include "SDL_ttf.h"

#include <iostream>

#define SCREENWIDTH 900
#define INFO_SIZE 300

#include "Game.hpp"

class SDL
{
	int screensize;
	int blocksize;

	SDL_Window *window;
	SDL_Surface *surface;

	// SDL_Color color_snake;
	// SDL_Color color_ground;
	// SDL_Color color_food;
	// SDL_Color color_barrier;
	SDL_Color color_text;
	// SDL_Color color_info_block;

	SDL_Rect block;
	SDL_Rect info;

	TTF_Font* font;

public:
	SDL(int);
	~SDL();

	void init(char **map, Game &game);
	void destroy();
	void draw(char **map, Game &game);
	void execute(Game &game);

	void set_pixel(SDL_Surface *surface, int i, int j, Uint32 pixel);
};