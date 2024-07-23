

NAME := cub3D

CC := cc
	
CFLAGS := -Wextra -Wall -Werror -Ofast # -fsanitize=address -g

# Directories
OBJDIR := obj
MLX := lib/MLX42/build/libmlx42.a
MLX_DIR := lib/MLX42
MLX_INCLUDES := $(MLX_DIR)/include/MLX42
LIB := lib/libft/libft.a
LIB_DIR := lib/libft
LIB_INCLUDES := $(LIB_DIR)/include
SRC_DIR := src
HEADERS_DIR := include

HEADERS := cub3d.h draw.h input.h parsing.h player.h static.h utils.h window.h

SUB_DIRS := parsing init static draw input player_movement utils
SRC_DIRS := $(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SUB_DIRS))
# Source files
SRC_FILES := \
	free.c \
	ft_validate_input.c \
	load_data.c \
	map_utility.c \
	map.c \
	rgb.c \
	textures_rgb.c \
	textures.c \
	validate_map.c \
	static_data.c \
	init_window.c \
	init_texture.c \
	init_data.c \
	init_player.c \
	init_map.c \
	draw_floor_and_cealing.c \
	draw_spites.c \
	draw_line.c \
	draw_walls.c \
	wasd_key_input.c \
	check_possible_move.c \
	move_player.c \
	rotate_player_via_mouse.c \
	key_handler.c \
	mouse_handler.c \
	cub3d.c \
	exit.c \
	get_pixel_from_image.c \
	calculate_rays.c \
	determine_direction.c \
	init_raycast_data.c \
	resize_handler.c \
	minimap.c

# Include directory for headers
INCLUDES := -I$(LIB_INCLUDES) -I$(HEADERS_DIR) -I$(MLX_INCLUDES)

# Object files
OBJS := $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))

# Total number of objects (for progress bar)
TOTAL := $(words $(OBJS))
CURRENT := 0

# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
NC := \033[0m # No Color

define ASCII_HEADER

 ██████╗██╗   ██╗██████╗     ██████╗ ██████╗
██╔════╝██║   ██║██╔══██╗    ╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝     █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗     ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝    ██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝     ╚═════╝ ╚═════╝

endef
export ASCII_HEADER

# Detect the operating system
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS := -lGL -lGLU -lX11 -lXext -lXrandr -lpthread -lm -lglfw
else ifeq ($(UNAME_S),Darwin)
	LIBS := -framework Cocoa -framework OpenGL -framework IOKit -lglfw
endif

# VPATH
vpath %.c $(SRC_DIRS)
vpath %.h $(HEADERS_DIR)

# File to track changes in bonus mode
BONUS_FLAG_FILE := .bonus_mode

# Create obj directory and compile the project
all: check_bonus_mode submodule start_build $(NAME)

check_bonus_mode:
	@if [ -f $(BONUS_FLAG_FILE) ]; then \
	   echo "Cleaning bonus mode..."; \
	   rm -f $(BONUS_FLAG_FILE); \
	   $(MAKE) clean; \
	fi

start_build:
	@echo "$$ASCII_HEADER"
	@if [ -n "`find $(SRC_DIR) -name '*.c' -newer $(NAME) 2>/dev/null`" ] || [ ! -f "$(NAME)" ]; then \
	   printf "$(YELLOW)Building cub3d project...$(NC)\n"; \
	else \
	   printf "$(GREEN)cub3d project is up to date. Nothing to build.$(NC)\n"; \
	fi

$(NAME): $(MLX) $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIB_DIR) -lft -L$(MLX_DIR)/build -lmlx42 $(LIBS)
	@printf "$(GREEN)cub3d project built.$(NC)\n"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(eval CURRENT=$(shell echo $$(($(CURRENT) + 1))))
	$(eval PERCENT=$(shell echo $$((100 * $(CURRENT) / $(TOTAL)))))
	$(eval HASHES=$(shell echo $$((50 * $(CURRENT) / $(TOTAL)))))
	$(eval SPACES=$(shell echo $$((50 - $(HASHES)))))
	@printf "\r$(YELLOW)Progress: [$(NC)%-50s$(YELLOW)] %2d%%$(NC)" $$(printf '%*s' $(HASHES) | tr ' ' '#')$$(printf '%*s' $(SPACES) ' ') $(PERCENT)
	@echo -n
	@if [ $(CURRENT) -eq $(TOTAL) ]; then echo ""; fi

# Clean rule
clean:
	@printf "$(RED)Cleaning objects...$(NC)\n"
	@rm -rf $(OBJDIR)
	@make -C $(LIB_DIR) clean
	@[ ! -d "$(MLX_DIR)/build" ] || make -C $(MLX_DIR)/build clean
	@printf "$(RED)Objects cleaned.$(NC)\n"

# Clean and remove executable rule
fclean: clean
	@printf "$(RED)Removing cub3d project...$(NC)\n"
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@printf "$(RED)cub3d project removed.$(NC)\n"

# Rebuild rule
re: fclean all

$(LIB):
	@make -C $(LIB_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
	   mkdir -p $(MLX_DIR)/build; \
	fi
	cd $(MLX_DIR)/build && cmake .. && make -j4

submodule:
	@if [ ! -f "./lib/libft/.git" ] && [ ! -d "./lib/libft/.git" ]; then \
	   echo "libft submodule not found. Initializing and updating libft submodule..."; \
	   git submodule update --init --recursive lib/libft; \
	else \
	   echo "libft submodule already initialized. Updating libft submodule..."; \
	   git submodule update --remote lib/libft; \
	fi
	@if [ ! -f "./lib/MLX42/.git" ] && [ ! -d "./lib/MLX42/.git" ]; then \
	   echo "MLX42 submodule not found. Initializing and updating MLX42 submodule..."; \
	   git submodule update --init --recursive lib/MLX42; \
	else \
	   echo "MLX42 submodule already initialized. Updating MLX42 submodule..."; \
	   git submodule update --remote lib/MLX42; \
	fi

sanitize: CFLAGS += -g -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
sanitize: clean all

leaks: CFLAGS += -g -DLEAKS
# leaks: make all
leaks: all

# Bonus rule
bonus: CFLAGS += -D IS_BONUS
bonus: fclean $(BONUS_FLAG_FILE) submodule start_build $(NAME)

$(BONUS_FLAG_FILE):
	@echo "Switching to bonus mode..."
	@touch $(BONUS_FLAG_FILE)

.PHONY: all check_bonus_mode clean fclean re start_build submodule sanitize leaks bonus
