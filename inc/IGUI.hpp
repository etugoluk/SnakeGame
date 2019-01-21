#ifndef IGUI_HPP
# define IGUI_HPP

#include "../inc/Game.hpp"

class IGUI
{
protected:
	int screensize;
public:
	IGUI(int screensize) : screensize(screensize){}
	// virtual IGUI* newGUI(int screensize) = 0;

	virtual void init(char **map, Game &game) = 0;
	virtual void destroy() = 0;
	virtual void draw(char **map, Game &game) = 0;
	virtual void execute(Game &game) = 0;
};

#endif