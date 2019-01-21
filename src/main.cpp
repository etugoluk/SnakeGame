
#include "../inc/Game.hpp"
#include "../inc/IGUI.hpp"
#include <dlfcn.h>

int main(){

	void *handle;

	handle = dlopen("SDL/sdl_lib.so", RTLD_LAZY);
     if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    IGUI   *(*create)(int) = nullptr;
    if (( create = reinterpret_cast<IGUI* (*)(int)>(dlsym(handle, "newGUI")) ) == nullptr)
        std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;

    int map_size = 30;
    Game game(map_size);
    game.update(' ');
    game.printMap();

    IGUI   *lib = create(map_size);
    lib->init(game.getMap());
    lib->execute(game);
    lib->destroy();

    return (0);
}
