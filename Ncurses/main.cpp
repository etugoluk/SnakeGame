#include "Ncurses.hpp"

extern "C" IGUI* newGUI(int screensize)
{
	return new NCURSES(screensize);
}

int main()
{
	int map_size = 30;
	Game game(map_size);
	IGUI *lib = newGUI(map_size);
    lib->init(game);
    lib->execute(game);
    lib->destroy();
	return 0;
}