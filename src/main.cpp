
#include "../inc/Game.hpp"
#include "../inc/SDL.hpp"

int main(){

    Game game(11);
    game.update("ta");
    game.printMap();

    SDL sdl;

    sdl.init(game.getMap());

    SDL_Event e;
    while (1)
    {
        std::string myInput;
        std::getline (std::cin,myInput);
        if (!game.update(myInput))
            break;
        game.printMap();
        sdl.draw(game.getMap());
        if (myInput == "q")
            break;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                break;
        }
    }

    sdl.destroy();
    return (0);
}
