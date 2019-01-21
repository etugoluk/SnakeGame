// #include <SDL2/SDL.h>
// # include "SDL_ttf.h"
#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"
// #include "./SDL/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
// #include "./SDL/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
// #include "../inc/Game.hpp"
// # include <SDL2/SDL.h>
// # include <SDL2/SDL_image.h>
// # include <SDL2/SDL_ttf.h>
#include <iostream>
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
	SDL_Rect info;
	// SDL_Rect img;

	// TTF_Font* font;

public:
	SDL(int);
	~SDL();
	// IGUI* newGUI(int screensize);

	void init(char **map);
	void destroy();
	void draw(char **map);
	void execute(Game &game);

	void set_pixel(SDL_Surface *surface, int i, int j, Uint32 pixel);
};