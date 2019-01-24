#include "SDL.hpp"

#include <unistd.h>

extern "C" IGUI* newGUI(Game &game)
{
	return new SDL(game);
}

SDL::SDL(Game &game) : IGUI(game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	throw SDL::InitException();

    if (!(window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH + INFO_SIZE, SCREENWIDTH , SDL_WINDOW_SHOWN)))
        throw SDL::CreateWindowException();

    if (!(surface = SDL_GetWindowSurface(window)))
    	throw SDL::SurfaceException();

    blocksize = SCREENWIDTH / screensize;

	color_text = {255, 255, 255, 255};
    block = {0, 0, blocksize, blocksize};

    int distance = 40;

    label = {blocksize * screensize + 50, 30, INFO_SIZE, 30};
    score = {blocksize * screensize + distance + 70, SCREENWIDTH / 2 - 100, INFO_SIZE, 40};
    level = {blocksize * screensize + distance + 70, SCREENWIDTH / 2 - 70, INFO_SIZE, 40};

    change = {blocksize * screensize + distance, SCREENWIDTH / 2 + 120, INFO_SIZE, 30};
    gui1 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 150, INFO_SIZE, 30};
    gui2 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 180, INFO_SIZE, 30};
    gui3 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 210, INFO_SIZE, 30};

    if (TTF_Init() != 0)
    	throw SDL::TTFException();

    if (!(font = TTF_OpenFont("SDL/font/BigCaslon.ttf", 26)))
    	throw SDL::FontException();

    background_color = 0xf4ee00;
	draw(game);
}

SDL::~SDL()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
    SDL_Quit();
}


// void     SDL::set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
// {
// 	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
// 	*(Uint32 *)target_pixel = pixel;
// }
	

void     SDL::set_block(SDL_Surface *surface, int i, int j, Uint32 pixel)
{
	for (int x = i; x < i + blocksize; ++x)
	{
		for (int y = j; y < j + blocksize; ++y)
		{
			Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    		*(Uint32 *)target_pixel = pixel;
		}
	}
}

void SDL::draw(Game &game)
{
	char** map = game.getMap();

	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			if (map[j][i] == 's')
				set_block(surface, i * blocksize, j * blocksize, 0xf4ee00);
			else if (map[j][i] == 'f')
				set_block(surface, i * blocksize, j * blocksize, 0xff6600);
			else if (map[j][i] == 'b')
				set_block(surface, i * blocksize, j * blocksize, 0x00CCCC);
			else
				set_block(surface, i * blocksize, j * blocksize, background_color);
		}
	}

	std::string inf;
	SDL_Surface* TTF_TextSolid;

	SDL_Rect rect = {blocksize * screensize, 0, INFO_SIZE, SCREENWIDTH};
	SDL_FillRect(surface, &rect, 0x009999);

	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, "NIBBLER GAME", color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &label);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Score: " + std::to_string(game.getScore());
	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &score);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Level: " + std::to_string(game.getLevel());
	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &level);
	SDL_FreeSurface(TTF_TextSolid);

	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, "To change GUI press:", color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &change);
	SDL_FreeSurface(TTF_TextSolid);

	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, "1 - classic", color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui1);
	SDL_FreeSurface(TTF_TextSolid);

	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, "2 - unit (now)", color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui2);
	SDL_FreeSurface(TTF_TextSolid);

	if (!(TTF_TextSolid = TTF_RenderText_Solid(font, "3 - minimal", color_text)))
		throw SDL::SurfaceException();
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui3);
	SDL_FreeSurface(TTF_TextSolid);

	SDL_UpdateWindowSurface(window);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
}

int SDL::execute(Game &game)
{
	char ch = 0;

	int r = 246;
	int g = 255;
	int b = 246;
	int k = 1;
	int *n = &b;

	while (1)
	{
		background_color = r * 256 * 256 + g * 256 + b;
		SDL_Event e;
		switch (game.snake.getHeadDirection())
    	{
    		case Top:
        		ch = 126;
        		break;
        	case Bottom:
        		ch = 125;
        		break;
        	case Left:
        		ch = 123;
        		break;
        	case Right:
        		ch = 124;
        		break;
    	}
		while (SDL_PollEvent(&e))
	    {
        	if (e.type == SDL_KEYDOWN)
        	{
        		switch (e.key.keysym.sym)
        		{
        			case SDLK_RIGHT:
		                ch = 124;
		                break;
		            case SDLK_DOWN:
		                ch = 125;
		                break;
		            case SDLK_LEFT:
		                ch = 123;
		                break;
		            case SDLK_UP:
		                ch = 126;
		                break;
		            case SDLK_ESCAPE:
		            	return 0;
               			break;
               		case SDLK_1:
		            	return 1;
               			break;
        		}
        	}
            if (e.type == SDL_QUIT)
                return 0;
	    }
    	if (!game.update(ch))
        	return 0;
        draw(game);
        usleep(300000 / game.getLevel());
        *n += k;
        if (*n == 255 || *n == 246)
        {
        	k *= -1;
        	if (n == &b)
        		n = &g;
        	else if (n == &r)
        		n = &b;
        	else
        		n = &r;
        }
	}
	return 0;
}

const char*    SDL::InitException::what() const throw() {
	return ("SDL: SDL_Init Error");
}

const char*    SDL::CreateWindowException::what() const throw() {
	return ("SDL: SDL_CreateWindow Error");
}

const char*    SDL::TTFException::what() const throw() {
	return ("SDL: TTF_Init Error");
}

const char*    SDL::FontException::what() const throw() {
	return ("SDL: TTF_OpenFont Error");
}

const char*    SDL::SurfaceException::what() const throw() {
	return ("SDL: Create_Surface Error");
}

