
#include "../inc/Game.hpp"

Game::Game(long screenLength) {
    srand(unsigned(std::time(0)));
    this->screenLength = screenLength;
    score = 0;
    level = 1;
    createMap();
    snake = Snake(screenLength);
    fillMap();
    fillSnakeWith('s');
    createBarriers(screenLength / 4);
    createFood();
}

Game::Game() = default;
Game::~Game() { destroyMap(); }

void
Game::createMap() {
    map = new char *[screenLength];
    for (auto i = 0; i != screenLength; ++i)
        map[i] = new char[screenLength];
}

void
Game::fillMap() {
    for (auto i = 0; i < screenLength; ++i) {
        for (auto j = 0; j < screenLength; ++j) {
            map[i][j] = '.';
        }
    }
    std::vector<std::pair<int, int> > snakeBody = snake.getBody();
    for(auto v : snakeBody)
        map[v.second][v.first] = 's';
}

void
Game::fillSnakeWith(char c) {
    std::vector<std::pair<int, int>> snakeBody = snake.getBody();
    for(auto v : snakeBody)
        map[v.second][v.first] = c;
}

void
Game::printMap() {
    for (auto i = 0; i < screenLength; ++i) {
        for (auto j = 0; j < screenLength; ++j)
            std::cout << map[i][j] << " ";
        std::cout << std::endl;
    }
}

void
Game::moveSnake(char c) {
    if (c == 'w' || c == 126)
        snake.moveSnake(UpArrow);
    else if (c == 's' || c == 125)
        snake.moveSnake(DownArrow);
    else if (c == 'a' || c == 123)
        snake.moveSnake(LeftArrow);
    else if (c == 'd' || c == 124)
        snake.moveSnake(RightArrow);
}

bool
Game::update(char c) {

    static int flag = 0;
    if (flag)
    {
        snake.extendTail();
        flag = 0;
    }
    fillSnakeWith('.');
    moveSnake(c);
    if (checkCollisions())
        return false;
    if (map[snake.getBody().at(0).second][snake.getBody().at(0).first] == 'f' && ++score)
    {
        flag = 1;
        fillSnakeWith('s');
        if (!(score % 5))
            changeLevel();
        createFood();
    }
    else
        fillSnakeWith('s');
    return true;
}

void
Game::changeLevel() {
    level++;
    createBarriers(2);
}

bool
Game::checkCollisions(){
    std::vector<std::pair<int, int> > snakeBody = snake.getBody();
    for(auto v : snakeBody)
        if (snake.borderHeadCollision() || snake.headBodyCollision() || map[v.second][v.first] == 'b')
            return true;
    return false;
}

void
Game::destroyMap() {
    for (auto i = 0; i != screenLength; ++i)
        delete [] map[i];
    delete [] map;
}

bool
Game::checkCoordsForBarriers(int x, int y)
{
    if (x >= screenLength - 1 || y >= screenLength - 1)
        return false;
    if ((map[x][y] != '.' || map[x + 1][y] != '.' || map[x][y + 1] != '.' || map[x + 1][y + 1] != '.'))
        return false;
    if (!score && (x == screenLength / 2 || (x + 1) == screenLength / 2))
        return false;
    return true;
}

void
Game::createBarriers(long size)
{
    long x, y;

    for (auto i = 0; i < size; ++i)
    {
        while (1)
        {
            x = rand() % screenLength;
            y = rand() % screenLength;
            if (checkCoordsForBarriers(x, y))
            {
                map[x][y] = 'b';
                map[x + 1][y] = 'b';
                map[x][y + 1] = 'b';
                map[x + 1][y + 1] = 'b';
                break;
            }
        }
    }
}

void
Game::createFood()
{
    long x, y;

    do
    {
        x = rand() % screenLength;
        y = rand() % screenLength;
    }
    while (map[x][y] != '.');

    map[x][y] = 'f';
}

char**
Game::getMap()
{
    return map;
}

int Game::getLevel()
{
    return level;
}

int Game::getScore()
{
    return score;
}

int Game::getScreenLength()
{
    return screenLength;
}
