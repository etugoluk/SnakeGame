
#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

enum snakeDirection {
    Top = 1,
    Bottom = -1,
    Left = 2,
    Right = -2
};

enum turnKey {
    UpArrow = 1, //38
    DownArrow = -1, //40
    LeftArrow = 2, //37
    RightArrow = -2 //39
};

class Snake {

public:
    explicit Snake(unsigned screenLengthn);
    Snake();
    ~Snake();

    void createSnake();

    void moveSnake(turnKey key);
    void moveHeadByDirection();
    void moveHeadUpDown(turnKey key);
    void moveHeadLeftRight(turnKey key);

    void extendTail();

    bool headBodyCollision();
    bool borderHeadCollision();

    void showBodyCoordinates();

    int getLength();
    snakeDirection getHeadDirection();
    std::vector<std::pair<int, int> > getBody();

private:
    long length;
    long screenLength;
    snakeDirection headDirection;
    std::vector<std::pair<int, int> > body; //(x1, y1),....(xn, yn) .push_back(std::make_pair(1,2));
};

#endif //NIBBLER_SNAKE_HPP
