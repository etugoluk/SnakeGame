#include <SDL2/SDL.h>

#include <iostream>

class SDL
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	// SDL_Surface *surface;
	SDL_Texture *texture;
public:
	SDL(char **map);
	~SDL();

	void draw(char **map);
};