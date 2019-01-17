//
// Created by Anastasiia ORJI on 2019-01-15.
//

#include "../inc/Snake.hpp"

Snake::Snake(unsigned length): length(4),
                          screenLength(length),
                          headDirection(Left)
                          { createSnake(); }

Snake::Snake() = default;
Snake::~Snake() = default;

void
Snake::createSnake() {
    long i = screenLength/2;
    for(int d = -2; d <= 1; ++d)
        body.emplace_back(std::make_pair(i + d, i));
}

void
Snake::moveSnake(turnKey key) {
    if ((int)key == -(int)headDirection)
        return;
    for (int i = length - 1; i > 0; --i) //Tail
        body.at(i) = std::make_pair(body.at(i - 1).first, body.at(i - 1).second);
    //Head
    if ((int)key == (int)headDirection)
        moveHeadByDirection();
    else if (headDirection == Left || headDirection == Right)
        moveHeadUpDown(key);
    else if (headDirection == Top || headDirection == Bottom)
        moveHeadLeftRight(key);
}

void
Snake::moveHeadByDirection() {
    if (headDirection == Top)
        body.at(0) = std::make_pair(body.at(0).first, body.at(0).second - 1);
    else if (headDirection == Bottom)
        body.at(0) = std::make_pair(body.at(0).first, body.at(0).second + 1);
    else if (headDirection == Left)
        body.at(0) = std::make_pair(body.at(0).first - 1, body.at(0).second);
    else if (headDirection == Right)
        body.at(0) = std::make_pair(body.at(0).first + 1, body.at(0).second);
}

void
Snake::moveHeadUpDown(turnKey key) {
    if (key == UpArrow) {
        body.at(0) = std::make_pair(body.at(0).first, body.at(0).second - 1);
        headDirection = Top;
    }
    else if (key == DownArrow) {
        body.at(0) = std::make_pair(body.at(0).first, body.at(0).second + 1);
        headDirection = Bottom;
    }
}

void
Snake::moveHeadLeftRight(turnKey key) {
    if (key == LeftArrow) {
        body.at(0) = std::make_pair(body.at(0).first - 1, body.at(0).second);
        headDirection = Left;
    }
    else if (key == RightArrow) {
        body.at(0) = std::make_pair(body.at(0).first + 1, body.at(0).second);
        headDirection = Right;
    }
}

void
Snake::extendTail() {
    if (body.at(length - 2).second > body.at(length - 1).second)
        body.emplace_back(std::make_pair(body.at(length - 1).first, body.at(length - 1).second - 1));
    else if (body.at(length - 2).second < body.at(length - 1).second)
        body.emplace_back(std::make_pair(body.at(length - 1).first, body.at(length - 1).second + 1));
    else if (body.at(length - 2).first > body.at(length - 1).first)
        body.emplace_back(std::make_pair(body.at(length - 1).first - 1, body.at(length - 1).second));
    else if (body.at(length - 2).first < body.at(length - 1).first)
        body.emplace_back(std::make_pair(body.at(length - 1).first + 1, body.at(length - 1).second));
    this->length++;
}

bool
Snake::headBodyCollision() {
    std::pair<int, int> head = body.at(0);
    for(auto i = 1; i < length ; ++i)
        if (head == body.at(i))
            return true;
    return false;
}

bool
Snake::borderHeadCollision() {
    for(auto i = 0; i < length ; ++i)
        if (body.at(i).first == screenLength || body.at(i).second == screenLength ||
                body.at(i).first == -1 || body.at(i).second == -1)
            return true;
    return false;
}

void
Snake::showBodyCoordinates() {
    for(auto v : body)
        std::cout << v.first << "," << v.second << std::endl;
}

//get
int
Snake::getLength() {
    return body.size();
}

snakeDirection
Snake::getHeadDirection() {
    return headDirection;
}

std::vector<std::pair<int, int>>
Snake::getBody() {
    return body;
}