#include "../inc/SDL.hpp"

SDL::SDL(int screensize) : screensize(screensize)
{}

SDL::~SDL()
{}

void SDL::init(char **map)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	std::cout << "SDLDisplay::InitException" << std::endl;

    window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BLOCK_SIZE * screensize, BLOCK_SIZE * screensize , SDL_WINDOW_SHOWN);
    if (!window)
         std::cout << "Bad window" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

	block.x = 0;
	block.y = 0;
	block.w = BLOCK_SIZE;
	block.h = BLOCK_SIZE;
	draw(map);
}

void SDL::destroy()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::draw(char **map)
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			block.x = i * BLOCK_SIZE;
			block.y = j * BLOCK_SIZE;

			SDL_QueryTexture(texture, nullptr, nullptr, &block.w, &block.h);
			if (map[j][i] == 's')
				SDL_SetRenderDrawColor(renderer, 150, 90, 0, 255);
			else if (map[j][i] == 'f')
				SDL_SetRenderDrawColor(renderer, 255, 90, 0, 255);
			else if (map[j][i] == 'b')
				SDL_SetRenderDrawColor(renderer, 194, 194, 214, 255);
			else
				SDL_SetRenderDrawColor(renderer, 142, 223, 93, 255);
			SDL_RenderFillRect(renderer, &block);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}