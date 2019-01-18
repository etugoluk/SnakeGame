#include <SDL2/SDL.h>

#include <iostream>

#define BLOCK_SIZE 70

#include "Game.hpp"

class SDL
{
	int screensize;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Rect block;

	// SDL_Event e;

public:
	SDL(int);
	~SDL();

	void init(char **map);
	void destroy();
	void draw(char **map);
	void execute(Game &game);
};