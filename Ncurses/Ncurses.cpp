#include "Ncurses.hpp"
#include <unistd.h>

#define GRASS		1
#define SNAKE		2
#define FOOD		3
#define BARRIER		4

extern "C" IGUI* newGUI(Game &game)
{
	return new NCURSES(game);
}

NCURSES::NCURSES(Game &game) : IGUI(game)
{
	initscr();
	start_color();
	curs_set(0);
	cbreak();
	noecho();

	init_pair(GRASS, COLOR_GREEN, COLOR_GREEN);
	init_pair(SNAKE, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(FOOD, COLOR_RED, COLOR_RED);
	init_pair(BARRIER, COLOR_BLUE, COLOR_BLUE);

	blocksize = 2;

	draw(game);
}

NCURSES::~NCURSES()
{
	endwin();
}

void NCURSES::draw_block(int i, int j)
{
	for (int k = i * blocksize * 2; k < (i + 1) * blocksize * 2; ++k)
	{
		for (int l = j * blocksize; l < (j + 1) * blocksize; ++l)
		{
			mvaddch(l, k, ' ');
		}
	}
}

void NCURSES::draw(Game &game)
{
	char **map = game.getMap();

	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			if (map[j][i] == 's')
			{
				attron(COLOR_PAIR(SNAKE));
				draw_block(i, j);
				attroff(COLOR_PAIR(SNAKE));
			}
			else if (map[j][i] == 'f')
			{
				attron(COLOR_PAIR(FOOD));
				draw_block(i, j);
				attroff(COLOR_PAIR(FOOD));
			}
			else if (map[j][i] == 'b')
			{
				attron(COLOR_PAIR(BARRIER));
				draw_block(i, j);
				attroff(COLOR_PAIR(BARRIER));
			}
			else
			{
				attron(COLOR_PAIR(GRASS));
				draw_block(i, j);
				attroff(COLOR_PAIR(GRASS));
			}
		}
		printw("\n");
	}

	refresh();
    getch();
}

void NCURSES::draw_info(Game &game)
{
	refresh();

	std::string score = "SCORE: " + std::to_string(game.score);
	std::string level = "LEVEL: " + std::to_string(game.level);
	mvprintw(10, screensize * blocksize * 2 + 5, "NIBBLER GAME");
	mvprintw(12, screensize * blocksize * 2 + 5, score.c_str());
	mvprintw(14, screensize * blocksize * 2 + 5, level.c_str());
}

int NCURSES::execute(Game &game)
{
	int ch = 0;
	keypad(stdscr, true);
	// nodelay(stdscr, TRUE);

	while (ch != 'q' && ch != KEY_EXIT)
	{
		// if ((ch = getch()) == ERR)
		// {
		// 	switch (game.snake.getHeadDirection())
		// 	{
	 //    		case Top:
	 //        		ch = 126;
	 //        		break;
	 //        	case Bottom:
	 //        		ch = 125;
	 //        		break;
	 //        	case Left:
	 //        		ch = 123;
	 //        		break;
	 //        	case Right:
	 //        		ch = 124;
	 //        		break;
		// 	 }
		// 	 break;
  // //       }
		ch = getch();
		switch (ch)
		{
			case KEY_RIGHT:
				ch = 124;
				break;
			case KEY_LEFT:
				ch = 123;
				break;
			case KEY_UP:
				ch = 126;
				break;
			case KEY_DOWN:
				ch = 125;
				break;
			case '2':
				return 2;
				break;
		}
		if (!game.update(ch))
			return 0;
		draw(game);
		draw_info(game);
		// usleep(300000);
	}
	return 0;
}
