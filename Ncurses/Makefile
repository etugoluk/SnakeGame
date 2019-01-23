NAME 		=	ncurses_lib.so

COM			=	clang++
FLAGS		=	-std=c++11 -Wall -Wextra -Werror -O3

LIB_FLAG	=	-lncurses -shared -nostartfiles -dynamiclib

SRC_FILES	=	../src/Game.cpp \
				../src/Snake.cpp  \
				Ncurses.cpp

INC_DIR		=	../includes

OBJ_FILES	= 	$(SRC_FILES:.cpp=.cpp.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ $(COM) $(FLAGS) $(LIB_FLAG) $(OBJ_FILES) -o $(NAME)

%.cpp.o:%.cpp
	@ $(COM) $(FLAGS) -c -o $@ $< -I $(INC_DIR)

clean:
	@ rm -rf $(OBJ_FILES)
	@ echo "\033[33mcleaned (Ncurses)\033[39m"

fclean:	clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (Ncurses)\033[39m"
	
re:	fclean all

.PHONY: all sdl clean fclean re