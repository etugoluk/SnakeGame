#ifndef NCURSES_HPP
#define NCURSES_HPP

#include "../inc/IGUI.hpp"
#include <ncurses.h>

class NCURSES : public IGUI
{
	int				blocksize;
public:
	NCURSES(Game &game);
	~NCURSES();

	// void init(Game &game);
	// void destroy();
	void draw(Game &game);
	int execute(Game &game);

	void draw_block(int i, int j);
	void draw_info(Game &game);
};

#endif