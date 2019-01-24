
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
    void fillSnakeWith(char c);
    void moveSnake(char c);

    void createFood();
    void createBarriers(long size);
    bool checkCoordsForBarriers(int x, int y);
    bool checkCollisions();

    void changeLevel();

    char **getMap() const;
    int getLevel() const;
    int getScore() const;
    int getScreenLength() const;
    Snake const & getSnake() const;

private:
    Game();
    char **map;
    int level;
    int score;
    long screenLength;
    Snake snake;
};

#endif //NIBBLER_GAME_HPP
