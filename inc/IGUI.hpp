#ifndef IGUI_HPP
# define IGUI_HPP

#include "Game.hpp"

#define SCREENWIDTH 900
#define INFO_SIZE 300

class IGUI
{
protected:
	int screensize;
public:
	IGUI(Game &game) : screensize(game.screenLength) {}

	virtual ~IGUI(){}
	// virtual void init(Game &game) = 0;
	// virtual void destroy() = 0;
	virtual void draw(Game &game) = 0;
	virtual int execute(Game &game) = 0;
};

#endif