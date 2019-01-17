//
// Created by Anastasiia ORJI on 2019-01-15.
//

#include "../inc/Game.hpp"
#include "../inc/SDL.hpp"
// #include <SDL2/SDL.h>

int main(){

    Game game(11);
    game.update("ta");
    game.printMap();

    SDL sdl(game.getMap());
    // if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    //     std::cout << "SDLDisplay::InitException" << std::endl;

    // SDL_Window *w = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);
    // if (!w)
    //      std::cout << "Bad window" << std::endl;

    // SDL_Surface *s = SDL_GetWindowSurface(w);
    // SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 142, 223, 93));
    // SDL_UpdateWindowSurface(w);
    // SDL_Delay(3000);

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

    return (0);
}
