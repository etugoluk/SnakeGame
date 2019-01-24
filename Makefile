NAME    =   snake
OBJ_DIR =   ./obj/
SRC_DIR =   ./src/
INC_DIR =   ./inc/

CC      =   clang++
FLAGS   =   -Wall -Wextra -Werror
SRC     =   main.cpp Snake.cpp Game.cpp Exception.cpp
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
HDRS    =   -I $(INC_DIR)

.SILENT:

all: $(NAME)

$(NAME): sdl ncurses $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(HDRS)
	echo "\033[32m[ ✔ ] "$(NAME) created" \033[0m"

sdl:
	@make -C SDL
	@echo "\033[32mSDL Builded\033[39m"

ncurses:
	@make -C Ncurses
	@echo "\033[32mNcurses Builded\033[39m"

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	@$(CC) -c $< -o $@ $(FLAGS) $(HDRS) -std=c++11

clean:
	@make -C SDL clean
	@make -C Ncurses clean
	rm -f $(OBJ)
	echo "\033[31m[ × ] "$(OBJ) removed" \033[0m"

fclean: clean
	@make -C SDL fclean
	@make -C Ncurses fclean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	echo "\033[31m[ × ] "$(NAME) removed" \033[0m"

re: fclean all

.PHONY: all ncurses sdl clean fclean re