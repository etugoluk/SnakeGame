
#include "../inc/Game.hpp"
#include "../inc/IGUI.hpp"
#include <dlfcn.h>
#include "../inc/Exception.hpp"

IGUI*   chooseLib(int res, int map_size)
{
    IGUI   *(*create)(Game) = nullptr;
    void *handle;

    if (res == 1)
        handle = dlopen("Ncurses/ncurses_lib.so", RTLD_LAZY);
    if (res == 2)
        handle = dlopen("SDL/sdl_lib.so", RTLD_LAZY);

    // if (res == 3)
    //     handle = dlopen("SDL/sfml_lib.so", RTLD_LAZY);

    if (!handle)
        throw InvalidLibrary();

    //newGUI - name of function in your library_name.cpp file. You create a pointer to this function and execute it.
    if (( create = reinterpret_cast<IGUI* (*)(Game)>(dlsym(handle, "newGUI")) ) == nullptr)
        throw InvalidLibraryFunction();

    return create(map_size);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        //nibbler instead of snake
        std::cout << "Usage: ./snake [map_size]" << std::endl;
        return 0;
    }
    try
    {
        int map_size = std::stoi(argv[1]);
        if (map_size < 20 || map_size > 50)
            throw InvalidSize();
        Game game(map_size);
        game.update(' ');

        //default lib = 1 (ncurses)
        IGUI   *lib = chooseLib(1, map_size);
        int res = 0; // 1 - ncurses, 2 - sdl, 3 - sfml
        while (1)
        {
            res = lib->execute(game);
            if (!res)
            {
                delete lib;
                exit(0);
            }
            if (res > 0)
            {
                delete lib;
                lib = chooseLib(res, map_size);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return (0);
}
