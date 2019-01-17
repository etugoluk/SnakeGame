NAME    =   nibbler
OBJ_DIR =   ./obj/
SRC_DIR =   ./src/
INC_DIR =   ./inc/

CC      =   clang++
FLAGS   =   -Wall -Wextra -Werror
SRC     =   main.cpp Snake.cpp Game.cpp SDL.cpp
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
HDRS    =   -I $(INC_DIR)

INCLUDES =	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/

FRAMEWORKS =	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(HDRS)  $(FRAMEWORKS)
	echo "\033[32m[ ✔ ] "$(NAME) created" \033[0m"

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	@$(CC) -c $< -o $@ $(FLAGS) $(HDRS) $(INCLUDES) -std=c++11

clean:
	rm -f $(OBJ)
	echo "\033[31m[ × ] "$(OBJ) removed" \033[0m"

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	echo "\033[31m[ × ] "$(NAME) removed" \033[0m"

re: fclean all