#include <SDL2/SDL.h>
# include "SDL_ttf.h"

#include <iostream>

#define BLOCK_SIZE 70
#define INFO_SIZE 300

#include "Game.hpp"

class SDL
{
	int screensize;

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

	void init(char **map);
	void destroy();
	void draw(char **map);
	void execute(Game &game);
};