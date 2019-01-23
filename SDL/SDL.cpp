#include "SDL.hpp"

#include <unistd.h>

extern "C" IGUI* newGUI(int screensize)
{
	return new SDL(screensize);
}

SDL::SDL(int screensize) : IGUI(screensize)
{}

SDL::~SDL()
{}

void SDL::init(Game &game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	std::cout << "SDLDisplay::InitException" << std::endl;

    window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH + INFO_SIZE, SCREENWIDTH , SDL_WINDOW_SHOWN);
    if (!window)
         std::cout << "Bad window" << std::endl;

    surface = SDL_GetWindowSurface(window);
    blocksize = SCREENWIDTH / screensize;

	color_text = {255, 255, 255, 255};
    block = {0, 0, blocksize, blocksize};

    int distance = 40;

    label = {blocksize * screensize + 60, 30, INFO_SIZE, 30};
    score = {blocksize * screensize + distance + 90, SCREENWIDTH / 2 - 100, INFO_SIZE, 30};
    level = {blocksize * screensize + distance + 90, SCREENWIDTH / 2 - 70, INFO_SIZE, 30};

    change = {blocksize * screensize + distance, SCREENWIDTH / 2 + 60, INFO_SIZE, 30};
    gui1 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 90, INFO_SIZE, 30};
    gui2 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 120, INFO_SIZE, 30};
    gui3 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 150, INFO_SIZE, 30};

    usage = {blocksize * screensize + distance, SCREENWIDTH / 2 + 210, INFO_SIZE, 30};
    arrow = {blocksize * screensize + distance, SCREENWIDTH / 2 + 240, INFO_SIZE, 60};

    // for (int i = SCREENWIDTH; i < SCREENWIDTH + INFO_SIZE; ++i)
    // {
    // 	for (int j = 0; j < SCREENWIDTH; ++j)
    // 	{
    // 		set_pixel(surface, i, j, 0x00CCCC);
    // 	}
    // }
    // info_block = SDL_CreateRGBSurface(0, INFO_SIZE, SCREENWIDTH, 32, 0, 119, 142, 255);
    // SDL_Rect r = {SCREENWIDTH, 0, INFO_SIZE, INFO_SIZE};
    // SDL_BlitSurface(info_block, NULL, surface, &r);
    // SDL_FreeSurface(info_block);

    TTF_Init();
    font = TTF_OpenFont("SDL/font/Arial.ttf", 20);

	draw(game, 0xf4ee00);
}

void SDL::destroy()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(food);
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

void SDL::draw(Game &game, int color)
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
				set_block(surface, i * blocksize, j * blocksize, color);
		}
	}

	std::string inf;
	SDL_Surface* TTF_TextSolid;

	TTF_TextSolid = TTF_RenderText_Solid(font, "NIBBLER GAME", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &label);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Score: " + std::to_string(game.score);
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &score);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Level: " + std::to_string(game.level);
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &level);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "To change GUI press:", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &change);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "1 - classic", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui1);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "2 - unit (now)", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui2);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "3 - minimal", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui3);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "Usage:", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &usage);
	SDL_FreeSurface(TTF_TextSolid);

	TTF_TextSolid = TTF_RenderText_Solid(font, "Use arrow keys to move the snake. Avoid barriers and borders.", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &arrow);
	SDL_FreeSurface(TTF_TextSolid);

	SDL_UpdateWindowSurface(window);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
}

void SDL::execute(Game &game)
{
	char ch = 0;

	int r = 246;
	int g = 255;
	int b = 246;
	int k = 1;

	int *n = &b;
	int counter;
	while (1)
	{
		counter = r * 256 * 256 + g * 256 + b;
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
		            	return ;
               			break;
        		}
        	}
            if (e.type == SDL_QUIT)
                return ;
	    }
    	if (!game.update(ch))
        	return ;
        draw(game, counter);
        usleep(300000 / game.level);
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
}
