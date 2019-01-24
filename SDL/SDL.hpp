#ifndef SDL_HPP
#define SDL_HPP

#include <iostream>

#include "./SDL/SDL2.framework/Versions/A/Headers/SDL.h"
#include "./SDL/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
#include "../inc/IGUI.hpp"

class SDL : public IGUI
{
	int blocksize;
	int background_color;

	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface* TTF_TextSolid;
	SDL_Color color_text;
	SDL_Event e;

	SDL_Rect block;

	//text blocks
	SDL_Rect label;
	SDL_Rect level;
	SDL_Rect score;
	SDL_Rect change;
	SDL_Rect gui1;
	SDL_Rect gui2;
	SDL_Rect gui3;

	TTF_Font* font;

public:
	SDL(Game &game);
	~SDL();

	void draw(Game &game);
	int drawBeginWindow();
	void drawEndWindow();
	int execute(Game &game);
	void getColor();

	// void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	void set_block(SDL_Surface *surface, int i, int j, Uint32 pixel);

	class InitException :public std::exception {
	public:
		virtual const char    *what() const throw();
	};

	class CreateWindowException :public std::exception {
	public:
		virtual const char    *what() const throw();
	};

	class TTFException :public std::exception {
	public:
		virtual const char    *what() const throw();
	};

	class FontException :public std::exception {
	public:
		virtual const char    *what() const throw();
	};

	class SurfaceException :public std::exception {
	public:
		virtual const char    *what() const throw();
	};
};

#endif