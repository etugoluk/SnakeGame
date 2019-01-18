#include "../inc/SDL.hpp"

SDL::SDL(int screensize) : screensize(screensize)
{}

SDL::~SDL()
{}

void SDL::init(char **map)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	std::cout << "SDLDisplay::InitException" << std::endl;

    window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BLOCK_SIZE * screensize + INFO_SIZE, BLOCK_SIZE * screensize , SDL_WINDOW_SHOWN);
    if (!window)
         std::cout << "Bad window" << std::endl;

    surface = SDL_GetWindowSurface(window);

 //    color_snake = {150, 90, 0, 255};
	// color_ground = {142, 223, 93, 255};
	// color_food = {255, 90, 0, 255};
	// color_barrier = {194, 194, 214, 255};
	color_text = {255, 255, 255, 255};
	// color_info_block = {0, 0, 0, 255};

    block = {0, 0, BLOCK_SIZE, BLOCK_SIZE};
    info = {BLOCK_SIZE * screensize, 0, INFO_SIZE, BLOCK_SIZE * screensize};

    font = TTF_OpenFont("font/ARIAL.TTF", 24);

	draw(map);
}

void SDL::destroy()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

void     set_pixel(SDL_Surface *surface, int i, int j, Uint32 pixel)
{
	for (int x = i; x < i + BLOCK_SIZE; ++x)
	{
		for (int y = j; y < j + BLOCK_SIZE; ++y)
		{
			Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    		*(Uint32 *)target_pixel = pixel;
		}
	}
}

void SDL::draw(char **map)
{
	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			if (map[j][i] == 's')
				set_pixel(surface, i * BLOCK_SIZE, j * BLOCK_SIZE, 0x965A00);
			else if (map[j][i] == 'f')
				set_pixel(surface, i * BLOCK_SIZE, j * BLOCK_SIZE, 0xFF5A00);
			else if (map[j][i] == 'b')
				set_pixel(surface, i * BLOCK_SIZE, j * BLOCK_SIZE, 0xC2C2D6);
			else
				set_pixel(surface, i * BLOCK_SIZE, j * BLOCK_SIZE, 0x8EDF5D);
		}
	}

	SDL_Surface *TTF_TextSolid = TTF_RenderText_Solid(font, "SCORE", color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &info);
	SDL_FreeSurface(TTF_TextSolid);

	SDL_UpdateWindowSurface(window);
}

void SDL::execute(Game &game)
{
	char ch = 0;

	while (1)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
	    {
        	if (e.type == SDL_KEYDOWN)
        	{
        		switch (e.key.keysym.sym)
        		{
        			case SDLK_RIGHT:
		                std::cout << "right" << std::endl;
		                ch = 124;
		                break;
		            case SDLK_DOWN:
		                std::cout << "down" << std::endl;
		                ch = 125;
		                break;
		            case SDLK_LEFT:
		                std::cout << "left" << std::endl;
		                ch = 123;
		                break;
		            case SDLK_UP:
		                std::cout << "up" << std::endl;
		                ch = 126;
		                break;
		            case SDLK_ESCAPE:
		            	return ;
               			break;
		            default:
		                ch = 0;
		                break;
        		}
        		std::cout << ch << std::endl;
		        if (!game.update(ch))
		        	return ;
		        draw(game.getMap());
        	}
            if (e.type == SDL_QUIT)
                return ;
	    }
	}
}