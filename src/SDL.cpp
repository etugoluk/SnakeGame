#include "../inc/SDL.hpp"

SDL::SDL(char **map)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	std::cout << "SDLDisplay::InitException" << std::endl;

    window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 840, SDL_WINDOW_SHOWN);
    if (!window)
         std::cout << "Bad window" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 70;
	r.h = 70;

	SDL_RenderClear(renderer);
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			r.x = i * 70;
			r.y = j * 70;

			// SDL_RenderClear(renderer);
			SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
			if (map[j][i] == 's')
				SDL_SetRenderDrawColor(renderer, 150, 90, 0, 255);
			else if (map[j][i] == 'f')
				SDL_SetRenderDrawColor(renderer, 255, 90, 0, 255);
			else if (map[j][i] == 'b')
				SDL_SetRenderDrawColor(renderer, 194, 194, 214, 255);
			else
				SDL_SetRenderDrawColor(renderer, 142, 223, 93, 255);
			SDL_RenderFillRect(renderer, &r);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
			// SDL_RenderPresent(renderer);
		}
	}

	// surface = SDL_LoadBMP("grass.bmp");
	// texture = SDL_CreateTextureFromSurface(renderer, surface);
	// SDL_FreeSurface(surface);

	SDL_RenderClear(renderer);
	// SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);
}

SDL::~SDL()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::draw(char **map)
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 70;
	r.h = 70;

	SDL_RenderClear(renderer);
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			r.x = i * 70;
			r.y = j * 70;

			SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
			if (map[j][i] == 's')
				SDL_SetRenderDrawColor(renderer, 150, 90, 0, 255);
			else if (map[j][i] == 'f')
				SDL_SetRenderDrawColor(renderer, 255, 90, 0, 255);
			else if (map[j][i] == 'b')
				SDL_SetRenderDrawColor(renderer, 194, 194, 214, 255);
			else
				SDL_SetRenderDrawColor(renderer, 142, 223, 93, 255);
			SDL_RenderFillRect(renderer, &r);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}