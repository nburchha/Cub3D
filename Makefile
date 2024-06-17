CC = cc

NAME = cub3d

LIB_DIR = inc/libs42
LIB = $(LIB_DIR)/libs42.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLXFLAGS = -L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL
MLX_PATH = MLX42/build
MLX42 = $(MLX_PATH)/libmlx42.a

INCLUDE_DIR = inc
HEADERS = cub3d.h

vpath %.h $(INCLUDE_DIR)

SRC_DIRS = src src/parsing src/graphics src/hooks src/player src/dda_algo
vpath %.c $(SRC_DIRS)

SRC = main.c parse.c texture.c map.c \
color.c check_map.c render_map.c \
util.c keyhook.c printing.c render_player.c \
general_hook.c movement.c dda_algo.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(MLX42) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) ./MLX42/build/libmlx42.a $(MLXFLAGS) $(LIB) $(CFLAGS) -I $(INCLUDE_DIR)

%.o: %.c $(HEADERS)
	@$(CC) -c $< -o $@ -I $(INCLUDE_DIR) $(CFLAGS)

$(MLX42):
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

$(LIB):
	$(MAKE) -c $(LIB_DIR)

clean:
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean
	@rm -rf MLX42/build

re: fclean all

.PHONY: clean fclean all re
