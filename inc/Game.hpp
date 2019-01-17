//
// Created by Anastasiia ORJI on 2019-01-16.
//

#ifndef NIBBLER_GAME_HPP
#define NIBBLER_GAME_HPP

#include "Snake.hpp"
#include <string>

class Game{
public:
    Game( long screenLength );
    ~Game();

    bool update(std::string c);
    void createMap();
    void destroyMap();
    void fillMap();
    void printMap();

    void createFood();
    void createBarriers();

    bool checkCollisions();

    void changeLevel();

    char **getMap();

private:
    Game();
    long screenLength;
    int score;
    int level;
    char **map;
    Snake snake;

};

#endif //NIBBLER_GAME_HPP
