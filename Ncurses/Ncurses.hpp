#ifndef NCURSES_HPP
#define NCURSES_HPP

#include "../inc/IGUI.hpp"
# include <mlx.h>

class NCURSES : public IGUI
{
	int				blocksize;

public:
	NCURSES(int);
	~NCURSES();

	void init(Game &game);
	// void destroy();
	void draw(Game &game);
	// void execute(Game &game);

	// void draw_block(int i, int j, int color);

};

#endif