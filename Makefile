# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_username <your_email@example.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 18:35:04 by your_username     #+#    #+#              #
#    Updated: 2024/07/02 18:35:04 by your_username    ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory
NAME := cub3D

# DIRECTORIES
SRC_DIRS := src \
            src/parsing \
            src/graphics \
            src/hooks \
            src/player \
            src/dda_algo

OBJ_DIR := obj
INC_DIR := inc
LIB_DIR := inc/libs42

# FILES
vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIR)

CFILES := main.c \
          parse.c \
          texture.c \
          map.c \
          color.c \
          check_map.c \
          util.c \
          keyhook.c \
          render_player.c \
          general_hook.c \
          movement.c \
          dda_algo.c \
          minimap.c \
          wall_collision.c \
          reset_canvas.c \
          minimap_player.c \
          cursor_hook.c \
          sprite.c \
          is_wall.c \
          dda_move.c \
          cast_projection.c

OFILES := $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

HEADER_FILES := cub3d.h

INCLUDES := -I$(INC_DIR)

# LIBS42
LIB := $(LIB_DIR)/libs42.a
INCLUDES += -I$(LIB_DIR)

# MLX42
MLX42_DIR := MLX42
MLX42 := $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS :=
ifeq ($(shell uname),Darwin)
    MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -framework OpenGL -framework Cocoa -lglfw
else ifeq ($(shell uname),Linux)
    MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -lglfw -ldl -pthread -lm
endif
INCLUDES += -I$(MLX42_DIR)/include/MLX42

# RULES
all: ascii $(NAME)

$(NAME): $(LIB) $(MLX42) $(OFILES)
	@printf "\n$(YELLOW)Compiling $(NAME)...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(OFILES) $(LIB) $(MLX42_FLAGS)
	@if [ -f $(NAME) ]; then \
		echo "$(GREEN)$(NAME) compiled successfully!$(NC)"; \
		echo "$(CYAN)Run with ./$(NAME)$(NC)"; \
		echo "------------------------------------------------"; \
	else \
		echo "$(RED)$(NAME) failed to compile$(NC)"; \
	fi

$(OBJ_DIR)/%.o: %.c $(HEADER_FILES) | $(OBJ_DIR)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)Compiling $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(ITALIC_LIGHT_YELLOW)$<$(NC) "
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)Creating obj directory...$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIB):
	@echo "$(YELLOW)Compiling libs42...$(NC)"
	@if [ ! -d $(LIB_DIR) ]; then mkdir -p $(LIB_DIR); fi
	@$(MAKE) -C $(LIB_DIR)

$(MLX42):
	@echo "$(YELLOW)Compiling MLX42...$(NC)"
	@if [ ! -d $(MLX42_DIR)/build ]; then mkdir -p $(MLX42_DIR)/build; fi
	@if [ ! -d $(MLX42_DIR) ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4

clean:
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@echo "$(RED)Removing object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaning libs42...$(NC)"
	@$(MAKE) -C $(LIB_DIR) clean
	@echo "$(RED)Cleaning MLX42...$(NC)"
	@$(MAKE) -C $(MLX42_DIR)/build clean

fclean: clean
	@echo "$(RED)Removing binary files...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

norm:
	@norminette $(SRC_DIRS) $(INC_DIR) $(LIB_DIR) | grep "Error" || echo "$(GREEN)Norme OK$(NC)"

debug: CFLAGS += -g
debug: CFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
debug: CFLAGS += -DDEBUG=1
debug: clean all

.PHONY: all clean fclean re norm ascii debug debug_thread

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
LIGHT_YELLOW = \033[0;93m
ITALIC_LIGHT_YELLOW = \033[3;93m
CYAN = \033[0;36m
NC = \033[0m
CLEAR_LINE = \033[2K\r

# Decoration
ascii:
	@echo "------------------------------------------------"
	@echo "$(CYAN)"
	@echo "             ______          _  ______"
	@echo "             | ___ \\        | ||  _  \\ "
	@echo "             | |_/ /   ___  | || | | |  ___  _ __"
	@echo "             | ___ \\  / _ \\ | || | | | / _ \\| '_ \\ "
	@echo "             | |_/ / |  __/ | || |/ / |  __/| | | |"
	@echo "             \\____/   \\___| |_||___/   \\___||_| |_|"
	@echo "$(NC)"
	@echo "------------------------------------------------"

BAR_WIDTH = 50
TOTAL_SRCS = $(words $(CFILES))
