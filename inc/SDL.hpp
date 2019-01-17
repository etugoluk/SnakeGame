#include <SDL2/SDL.h>

#include <iostream>

#define BLOCK_SIZE 70

class SDL
{
	int screensize;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;

	SDL_Rect block;

public:
	SDL(int);
	~SDL();

	void init(char **map);
	void destroy();
	void draw(char **map);
};