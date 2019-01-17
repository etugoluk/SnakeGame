#include <SDL2/SDL.h>

#include <iostream>

class SDL
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	// SDL_Surface *surface;
	SDL_Texture *texture;
public:
	SDL();
	~SDL();

	void draw(char **map);
	void init(char **map);
	void destroy();
};