
#include "../inc/Game.hpp"
#include "../inc/SDL.hpp"

int main(){

    Game game(11);
    game.update(' ');
    game.printMap();

    SDL sdl(11);

    sdl.init(game.getMap());

    sdl.execute(game);

    sdl.destroy();
    return (0);
}

// SDL_Event e;

    // char ch;
    // while (1)
    // {
    //     // std::cin >> ch;
    //     // if (ch == 'q')
    //     //     break;
    //     while (SDL_PollEvent(&e))
    //     {
    //         switch (e.type)
    //         {
    //             case SDL_QUIT:
    //                 return 0;
    //                 break;
    //             case SDLK_RIGHT:
    //                 std::cout << "right" << std::endl;
    //                 ch = 124;
    //                 break;
    //             case SDLK_DOWN:
    //                 std::cout << "down" << std::endl;
    //                 ch = 125;
    //                 break;
    //             case SDLK_LEFT:
    //                 std::cout << "left" << std::endl;
    //                 ch = 123;
    //                 break;
    //             case SDLK_UP:
    //                 std::cout << "up" << std::endl;
    //                 ch = 126;
    //                 break;
    //             default:
    //                 ch = 0;
    //                 break;
    //         }
    //         std::cout << ch << std::endl;
    //         game.update(ch);
    //         sdl.draw(game.getMap());
    //     }
    //     // game
    //     // if (!game.update(ch))
    //     //     break;
    //     // game.printMap();
    //     // sdl.draw(game.getMap());
    // }