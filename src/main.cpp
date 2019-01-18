
#include "../inc/Game.hpp"
#include "../inc/SDL.hpp"

int main(){

    int map_size = 30;

    Game game(map_size);
    game.update(' ');
    game.printMap();

    SDL sdl(map_size);
    sdl.init(game.getMap(), game);
    sdl.execute(game);
    sdl.destroy();

    return (0);
}
