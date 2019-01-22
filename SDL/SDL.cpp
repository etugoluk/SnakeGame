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

    label = {blocksize * screensize + distance, 30, INFO_SIZE, 30};
    score = {blocksize * screensize + distance, SCREENWIDTH / 2 - 30, INFO_SIZE, 30};
    level = {blocksize * screensize + distance, SCREENWIDTH / 2, INFO_SIZE, 30};

    change = {blocksize * screensize + distance, SCREENWIDTH / 2 + 60, INFO_SIZE, 30};
    gui1 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 90, INFO_SIZE, 30};
    gui2 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 120, INFO_SIZE, 30};
    gui3 = {blocksize * screensize + distance, SCREENWIDTH / 2 + 150, INFO_SIZE, 30};

    usage = {blocksize * screensize + distance, SCREENWIDTH / 2 + 210, INFO_SIZE, 30};
    arrow = {blocksize * screensize + distance, SCREENWIDTH / 2 + 240, INFO_SIZE, 60};

    // food = SDL_LoadBMP("SDL/images/foods.bmp");
    // if (!food)
    // 	std::cout << SDL_GetError() << std::endl;
    // food->w = blocksize;
    // food->h = blocksize;
    // scale_image(food, blocksize);
    TTF_Init();
    font = TTF_OpenFont("SDL/font/Arial.ttf", 24);

	draw(game);
}

void SDL::destroy()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(food);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

// Uint32	get_pixel2(SDL_Surface *sur, const int x, const int y)
// {
// 	uint8_t *v;
// 	int		bpp;

// 	if (x < 0 || x >= sur->w || y < 0 || y >= sur->h)
// 		return (0);
// 	bpp = sur->format->BytesPerPixel;
// 	v = (uint8_t *)sur->pixels + y * sur->pitch + x * bpp;
// 	return (v[0] | v[1] << 8 | v[2] << 16);
// }

void     SDL::set_pixel(SDL_Surface *surface, int i, int j, Uint32 pixel)
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

// void	scale_image(SDL_Surface *icon, float size)
// {
// 	int 		    y;
//     int             x;
// 	float 		    new_y;
//     float           new_x;
// 	float		    final_x;
// 	float			final_y;
// 	float 		    dy;
//     float           dx;

// 	new_y = 0;
// 	new_x = 0;
//     x = -1;

//     final_x = icon->w * scale; 
// 	dx =  (float)icon->w / final_x;
//     final_y = icon->h * scale;
// 	dy = (float)icon->h / final_y;

//     if (scale < 0.0)
//     {
//         final_x = icon->w; 
//         final_y = icon->h;
//     }
// 	while (++x < final_x )
// 	{
//         new_y = 0;
// 		y = -1;
// 		while (++y < final_y)
// 		{
// 			set_pixel(bmp, x, y, get_pixel2(icon, (int)new_x , (int)new_y));
// 			new_y += dy;
// 		}
// 		new_x += dx;
// 	}
// }

void SDL::draw(Game &game)
{
	char** map = game.getMap();

	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			if (map[j][i] == 's')
				set_pixel(surface, i * blocksize, j * blocksize, 0xf4ee00);
			else if (map[j][i] == 'f')
			{
			// 	img = {i * blocksize, j * blocksize, blocksize, blocksize};
			// 	SDL_BlitSurface(food, NULL, surface, &img);
			// 	SDL_UpdateWindowSurface(window);
				set_pixel(surface, i * blocksize, j * blocksize, 0xff6600);
			}
			else if (map[j][i] == 'b')
				set_pixel(surface, i * blocksize, j * blocksize, 0xe69900);
			else if (map[j][i] == '.' && ((!(j % 2) && !(i % 2)) || ((j % 2) && (i % 2))))
				set_pixel(surface, i * blocksize, j * blocksize, 0xb5dc00);
			else
				set_pixel(surface, i * blocksize, j * blocksize, 0xaadc00);
		}
	}

	std::string inf;
	SDL_Surface *TTF_TextSolid;

	inf = "NIBBLER GAME";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
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

	inf = "To change GUI press:";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &change);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "1 - classic";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui1);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "2 - unit (now)";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui2);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "3 - minimal";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &gui3);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Usage:";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &usage);
	SDL_FreeSurface(TTF_TextSolid);

	inf = "Use arrow keys to move the snake. Avoid barriers and borders.";
	TTF_TextSolid = TTF_RenderText_Solid(font, inf.c_str(), color_text);
	SDL_BlitSurface(TTF_TextSolid, NULL, surface, &arrow);
	SDL_FreeSurface(TTF_TextSolid);

	SDL_UpdateWindowSurface(window);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
}

void SDL::execute(Game &game)
{
	char ch = 0;

	while (1)
	{
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
        draw(game);
        usleep(300000 / game.level);
	}
}