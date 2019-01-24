#include "Ncurses.hpp"
#include <unistd.h>

#define GRASS		1
#define SNAKE		2
#define FOOD		3
#define BARRIER		4
#define TEXT		5
#define HEADSNAKE	6

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
	init_pair(TEXT, COLOR_GREEN, COLOR_BLACK);
	init_pair(HEADSNAKE, COLOR_MAGENTA, COLOR_MAGENTA);

	blocksize = 1;

	if (!drawBeginWindow())
    	exit(0);
	draw(game);
}

NCURSES::~NCURSES()
{
	endwin();
}

int NCURSES::drawBeginWindow()
{
	keypad(stdscr, true);
	nodelay(stdscr, FALSE);

	erase();
	attron(COLOR_PAIR(TEXT));
	mvprintw(0, 0, " ███▄    █  ██▓ ▄▄▄▄    ▄▄▄▄    ██▓    ▓█████  ██▀███  "); 
	mvprintw(1, 0, " ██ ▀█   █ ▓██▒▓█████▄ ▓█████▄ ▓██▒    ▓█   ▀ ▓██ ▒ ██▒");
	mvprintw(2, 0, "▓██  ▀█ ██▒▒██▒▒██▒ ▄██▒██▒ ▄██▒██░    ▒███   ▓██ ░▄█ ▒");
	mvprintw(3, 0, "▓██▒  ▐▌██▒░██░▒██░█▀  ▒██░█▀  ▒██░    ▒▓█  ▄ ▒██▀▀█▄  ");
	mvprintw(4, 0, "▒██░   ▓██░░██░░▓█  ▀█▓░▓█  ▀█▓░██████▒░▒████▒░██▓ ▒██▒");
	mvprintw(5, 0, "░ ▒░   ▒ ▒ ░▓  ░▒▓███▀▒░▒▓███▀▒░ ▒░▓  ░░░ ▒░ ░░ ▒▓ ░▒▓░");
	mvprintw(6, 0, "░ ░░   ░ ▒░ ▒ ░▒░▒   ░ ▒░▒   ░ ░ ░ ▒  ░ ░ ░  ░  ░▒ ░ ▒░");
	mvprintw(7, 0, "   ░   ░ ░  ▒ ░ ░    ░  ░    ░   ░ ░      ░     ░░   ░ ");
	mvprintw(8, 0, "         ░  ░   ░       ░          ░  ░   ░  ░   ░     ");
	mvprintw(9, 0, "                     ░       ░                         ");

	mvprintw(11, 16, "PLAY (press Enter key)");
	mvprintw(13, 16, "EXIT (press Esc key)");
	attroff(COLOR_PAIR(TEXT));

	char ch = getch();
	erase();
	if (ch == 10)
		return 1;
	if (ch == 27)
		return 0;
	return 0;
}

void NCURSES::drawEndWindow()
{
	erase();
	attron(COLOR_PAIR(TEXT));
	mvprintw(0, 0, " ███▄    █  ██▓ ▄▄▄▄    ▄▄▄▄    ██▓    ▓█████  ██▀███  "); 
	mvprintw(1, 0, " ██ ▀█   █ ▓██▒▓█████▄ ▓█████▄ ▓██▒    ▓█   ▀ ▓██ ▒ ██▒");
	mvprintw(2, 0, "▓██  ▀█ ██▒▒██▒▒██▒ ▄██▒██▒ ▄██▒██░    ▒███   ▓██ ░▄█ ▒");
	mvprintw(3, 0, "▓██▒  ▐▌██▒░██░▒██░█▀  ▒██░█▀  ▒██░    ▒▓█  ▄ ▒██▀▀█▄  ");
	mvprintw(4, 0, "▒██░   ▓██░░██░░▓█  ▀█▓░▓█  ▀█▓░██████▒░▒████▒░██▓ ▒██▒");
	mvprintw(5, 0, "░ ▒░   ▒ ▒ ░▓  ░▒▓███▀▒░▒▓███▀▒░ ▒░▓  ░░░ ▒░ ░░ ▒▓ ░▒▓░");
	mvprintw(6, 0, "░ ░░   ░ ▒░ ▒ ░▒░▒   ░ ▒░▒   ░ ░ ░ ▒  ░ ░ ░  ░  ░▒ ░ ▒░");
	mvprintw(7, 0, "   ░   ░ ░  ▒ ░ ░    ░  ░    ░   ░ ░      ░     ░░   ░ ");
	mvprintw(8, 0, "         ░  ░   ░       ░          ░  ░   ░  ░   ░     ");
	mvprintw(9, 0, "                     ░       ░                         ");
	mvprintw(11, 23, "GAME OVER");
	attroff(COLOR_PAIR(TEXT));
	refresh();
	sleep(3);
}

void NCURSES::drawBlock(int i, int j)
{
	for (int k = i * blocksize * 2; k < (i + 1) * blocksize * 2; ++k)
	{
		for (int l = j * blocksize; l < (j + 1) * blocksize; ++l)
		{
			mvaddch(l + 10, k, ' ');
		}
	}
}

void NCURSES::draw(Game &game)
{
	char **map = game.getMap();

	attron(COLOR_PAIR(TEXT));
	mvprintw(0, 0, " ███▄    █  ██▓ ▄▄▄▄    ▄▄▄▄    ██▓    ▓█████  ██▀███  "); 
	mvprintw(1, 0, " ██ ▀█   █ ▓██▒▓█████▄ ▓█████▄ ▓██▒    ▓█   ▀ ▓██ ▒ ██▒");
	mvprintw(2, 0, "▓██  ▀█ ██▒▒██▒▒██▒ ▄██▒██▒ ▄██▒██░    ▒███   ▓██ ░▄█ ▒");
	mvprintw(3, 0, "▓██▒  ▐▌██▒░██░▒██░█▀  ▒██░█▀  ▒██░    ▒▓█  ▄ ▒██▀▀█▄  ");
	mvprintw(4, 0, "▒██░   ▓██░░██░░▓█  ▀█▓░▓█  ▀█▓░██████▒░▒████▒░██▓ ▒██▒");
	mvprintw(5, 0, "░ ▒░   ▒ ▒ ░▓  ░▒▓███▀▒░▒▓███▀▒░ ▒░▓  ░░░ ▒░ ░░ ▒▓ ░▒▓░");
	mvprintw(6, 0, "░ ░░   ░ ▒░ ▒ ░▒░▒   ░ ▒░▒   ░ ░ ░ ▒  ░ ░ ░  ░  ░▒ ░ ▒░");
	mvprintw(7, 0, "   ░   ░ ░  ▒ ░ ░    ░  ░    ░   ░ ░      ░     ░░   ░ ");
	mvprintw(8, 0, "         ░  ░   ░       ░          ░  ░   ░  ░   ░     ");
	mvprintw(9, 0, "                     ░       ░                         ");
	attroff(COLOR_PAIR(TEXT));

	for (int i = 0; i < screensize; ++i)
	{
		for (int j = 0; j < screensize; ++j)
		{
			if (map[j][i] == 's')
			{
				attron(COLOR_PAIR(SNAKE));
				drawBlock(i, j);
				attroff(COLOR_PAIR(SNAKE));
			}
			else if (map[j][i] == 'o')
			{
				attron(COLOR_PAIR(HEADSNAKE));
				drawBlock(i, j);
				attroff(COLOR_PAIR(HEADSNAKE));
			}
			else if (map[j][i] == 'f')
			{
				attron(COLOR_PAIR(FOOD));
				drawBlock(i, j);
				attroff(COLOR_PAIR(FOOD));
			}
			else if (map[j][i] == 'b')
			{
				attron(COLOR_PAIR(BARRIER));
				drawBlock(i, j);
				attroff(COLOR_PAIR(BARRIER));
			}
			else
			{
				attron(COLOR_PAIR(GRASS));
				drawBlock(i, j);
				attroff(COLOR_PAIR(GRASS));
			}
		}
		printw("\n");
	}
	refresh();
}

void NCURSES::drawInfo(Game &game)
{
	refresh();
	
	std::string maxScore = "MAX SCORE: " + game.getMaxScore();
	std::string score = "SCORE: " + std::to_string(game.getScore());
	std::string level = "LEVEL: " + std::to_string(game.getLevel());

	attron(COLOR_PAIR(TEXT));
	mvprintw(12, screensize * blocksize * 2 + 5, maxScore.c_str());
	mvprintw(14, screensize * blocksize * 2 + 5, score.c_str());
	mvprintw(16, screensize * blocksize * 2 + 5, level.c_str());
	attroff(COLOR_PAIR(TEXT));
}

int NCURSES::execute(Game &game)
{
	int ch = 0;
	int dir = 0;
	keypad(stdscr, true);
	nodelay(stdscr, TRUE);

	while (1)
	{
		switch (game.getSnake().getHeadDirection())
		{
    		case Top:
        		dir = 126;
        		break;
        	case Bottom:
        		dir = 125;
        		break;
        	case Left:
        		dir = 123;
        		break;
        	case Right:
        		dir = 124;
        		break;
		 }
		if ((ch = getch()) == ERR)
			ch = dir;
		else
		{
			if (ch == KEY_RIGHT && dir != 123)
    			ch = 124;
    		else if (ch == KEY_DOWN && dir != 126)
    			ch = 125;
    		else if (ch == KEY_LEFT && dir != 124)
    			ch = 123;
    		else if (ch == KEY_UP && dir != 125)
    			ch = 126;
    		else if (ch == 27)
    			return 0;
    		else if (ch == 'q')
    			return 0;
    		else if (ch == '2')
    			return 2;
    		else
    			ch = dir;
		}
		if (!game.update(ch))
		{
			drawEndWindow();
			return 0;
		}
		draw(game);
		drawInfo(game);
		usleep(300000 / game.getLevel());
	}
	return 0;
}
