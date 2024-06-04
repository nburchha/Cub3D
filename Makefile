CC = cc

NAME = cub3d

LIB = inc/libs42/libs42.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLXFLAGS = -L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL

SRC = src/main.c

OBJ = $(SRC:.c=.o)

all: MLX42 $(NAME)

$(NAME): $(LIB) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) ./MLX42/build/libmlx42.a $(MLXFLAGS) $(LIB) $(CFLAGS)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

$(LIB):
	cd inc/libs42 && make

clean:
	@rm -rf MLX42
	@rm -f $(OBJ)
	@cd inc/libs42 && make clean

fclean: clean
	@rm -f $(NAME)
	@cd inc/libs42 && make fclean

re: fclean all

.PHONY: clean fclean all re