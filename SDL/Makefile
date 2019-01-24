NAME 		=	sdl_lib.so

COM			=	clang++
FLAGS		=	-std=c++11 -Wall -Wextra -Werror -O3

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2
SDL_LNK_TTF	=	-framework SDL2_ttf

PWD			= 	$(shell pwd)
LIB_FLAG	=	-shared  -rpath $(PWD)/$(SDL_DIR) -nostartfiles -dynamiclib

SRC_FILES	=	../src/Game.cpp \
				../src/Snake.cpp  \
				SDL.cpp

INC_FILES	=	SDL.hpp

OBJ_FILES	= 	$(SRC_FILES:.cpp=.cpp.o)

SDL2 		=	SDL2
SDL2_TTF	=	SDL2_TTF

all: sdl $(NAME)

$(NAME): $(OBJ_FILES)
	@ $(COM) $(FLAGS) $(SDL_FRM) $(SDL_LINK) $(SDL_LNK_TTF) $(LIB_FLAG) $(OBJ_FILES) -o $(NAME)

%.cpp.o:%.cpp
	@ $(COM) $(FLAGS) $(SDL_FRM) -c -o $@ $<


sdl:
	@ mkdir -p $(SDL_DIR)
	@ test -f SDL/SDL2.framework/SDL2 && echo "\033[33mFile $(SDL2) already exist\033[39m" || make sdl2_download
	@ test -f SDL/SDL2_ttf.framework/SDL2_ttf && echo "\033[33mFile $(SDL2_TTF) already exist\033[39m" || make sdl2_ttf_download

sdl2_download:
	echo "\033[32m... loading SDL\033[39m"
	@ curl -o sdl2.dmg https://www.libsdl.org/release/SDL2-2.0.8.dmg
	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; hdiutil eject ../../../Volumes/SDL2;
	@ rm -rf sdl2.dmg

sdl2_ttf_download:
	echo "\033[32m... loading SDL_ttf\033[39m"
	@ curl -o sdl2_ttf.dmg https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg
	@ hdiutil attach sdl2_ttf.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2_ttf/SDL2_ttf.framework $(PWD)/$(SDL_DIR)/SDL2_ttf.framework; hdiutil eject ../../../Volumes/SDL2_ttf;
	@ rm -rf sdl2_ttf.dmg

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -fr $(SDL_DIR)
	@ echo "\033[33mcleaned (SDL)\033[39m"

fclean:	clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (SDL)\033[39m"
	
re:	fclean all

.PHONY: all sdl clean fclean re