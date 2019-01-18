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
	SDL_Surface *food;
	SDL_Color color_text;

	SDL_Rect block;
	SDL_Rect info;
	SDL_Rect img;

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