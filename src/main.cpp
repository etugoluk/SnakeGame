
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

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    if (( create = reinterpret_cast<IGUI* (*)(Game)>(dlsym(handle, "newGUI")) ) == nullptr)
        std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;

    return create(map_size);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
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

        IGUI   *lib = chooseLib(1, map_size);

        int res = 0;
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
