#ifndef IGUI_HPP
# define IGUI_HPP

#include "../inc/Game.hpp"

class IGUI
{
protected:
	int screensize;
public:
	IGUI(int screensize) : screensize(screensize){}

	virtual void init(Game &game) = 0;
	virtual void destroy() = 0;
	virtual void draw(Game &game) = 0;
	virtual void execute(Game &game) = 0;
};

#endif