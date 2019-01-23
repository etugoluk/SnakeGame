#include "Ncurses.hpp"

NCURSES::NCURSES(int screensize) : IGUI(screensize)
{}

NCURSES::~NCURSES()
{}

// void v::init(Game &game)
// {
// 	std::string name =  "Nibbler";
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, SCREENWIDTH + INFO_SIZE, SCREENWIDTH, (char*)name.c_str());
// 	mlx_img = mlx_new_image(mlx, SCREENWIDTH + INFO_SIZE, SCREENWIDTH);

// 	blocksize = SCREENWIDTH / screensize;

// 	draw(game);
// }

// void MLX::destroy()
// {

// }

// void NCURSES::draw(Game &game)
// {
// 	char** map = game.getMap();

// 	for (int i = 0; i < screensize; ++i)
// 	{
// 		for (int j = 0; j < screensize; ++j)
// 		{
// 			if (map[j][i] == 's')
// 				draw_block(i * blocksize, j * blocksize, 0xf4ee00);
// 			else if (map[j][i] == 'f')
// 				draw_block(i * blocksize, j * blocksize, 0xff6600);
// 			else if (map[j][i] == 'b')
// 				draw_block(i * blocksize, j * blocksize, 0xe69900);
// 			else if (map[j][i] == '.' && ((!(j % 2) && !(i % 2)) || ((j % 2) && (i % 2))))
// 				draw_block(i * blocksize, j * blocksize, 0xb5dc00);
// 			else
// 				draw_block(i * blocksize, j * blocksize, 0xaadc00);
// 		}
// 	}
// }

// void NCURSES::draw_block(int i, int j, int color)
// {
// 	for (int x = i; x < i + blocksize; ++x)
// 	{
// 		for (int y = j; y < j + blocksize; ++y)
// 		{
// 			mlx_pixel_put_image(x, y, color);
// 		}
// 	}
// }

// void MLX::execute(Game &game)
// {
// 	mlx_loop(mlx);
// }
