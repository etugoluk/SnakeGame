
#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include <string>

class Game{
public:
    Game( long screenLength );
    ~Game();

    bool update(char c);
    void createMap();
    void destroyMap();
    void fillMap();
    void printMap();

    void createFood();
    void createBarriers(long size);

    bool checkCollisions();

    void changeLevel();

    char **getMap();

    Snake snake;

    int getLevel();
    int getScore();
    int getScreenLength();

private:
    Game();
    char **map;
    int level;
    int score;
    long screenLength;
};

#endif //NIBBLER_GAME_HPP
