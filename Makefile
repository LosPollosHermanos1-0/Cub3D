# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 11:23:35 by lzipp             #+#    #+#              #
#    Updated: 2024/06/14 12:57:08 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

CC := cc

REPO_DIR := MLX42
REPO_URL := https://github.com/codam-coding-college/MLX42.git

CFLAGS := -Wextra -Wall -Werror -Ofast

# Directories
OBJDIR := obj
LIB_DIR := libft
LIB_INCLUDES := $(LIB_DIR)/include
SRC_DIR := src
HEADERS_DIR := inc

# Additional source directories
SRC_DIRS := $(SRC_DIR) $(SRC_DIR)/parsing $(SRC_DIR)/init $(SRC_DIR)/static

# Source files
SRC_FILES := static_data.c init_window.c init_data.c cub3d.c

# Include directory for headers
INCLUDES := -I$(LIB_INCLUDES) -I$(HEADERS_DIR) -I$(REPO_DIR)/include/MLX42

# Object files
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC_FILES))

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

# VPATH
vpath %.c $(SRC_DIRS)

# Create obj directory and compile the project
all: clone_repo build_repo lib_make start_build $(NAME)

start_build:
	@echo "$$ASCII_HEADER"
	@if [ -n "`find $(SRC_DIR) -name '*.c' -newer $(NAME) 2>/dev/null`" ] || [ ! -f "$(NAME)" ]; then \
		printf "$(YELLOW)Building cub3d project...$(NC)\n"; \
	else \
		printf "$(GREEN)cub3d project is up to date. Nothing to build.$(NC)\n"; \
	fi

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L. $(LIB_DIR)/libft.a -L$(REPO_DIR)/lib -framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -lglfw
	@printf "$(GREEN)cub3d project built.$(NC)\n"

$(OBJDIR)/%.o: %.c $(HEADERS_DIR)/*.h
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
clean: lib_clean
	@printf "$(RED)Cleaning objects...$(NC)\n"
	@rm -rf $(OBJDIR)
	@printf "$(RED)Objects cleaned.$(NC)\n"

# Clean and remove executable rule
fclean: clean lib_fclean
	@printf "$(RED)Removing cub3d project...$(NC)\n"
	@rm -f $(NAME)
	@printf "$(RED)cub3d project removed.$(NC)\n"

# Rebuild rule
re: fclean all

lib_make:
	@make -C $(LIB_DIR)

lib_clean:
	@make -C $(LIB_DIR) clean

lib_fclean:
	@make -C $(LIB_DIR) fclean

# Clone the MLX42 Repository
clone_repo:
	@if [ ! -d "$(REPO_DIR)" ]; then \
		git clone $(REPO_URL); \
	fi

# Build the MLX42 Library
build_repo:
	@if [ ! -d "$(REPO_DIR)/build" ]; then \
		mkdir -p $(REPO_DIR)/build; \
	fi
	cd $(REPO_DIR)/build && cmake .. && make

submodule:
	@if [ ! -d "./libft/.git" ]; then \
		echo "Submodule not found. Initializing and updating submodule..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodule already initialized."; \
		git submodule update --remote; \
	fi

.PHONY: all clean fclean re start_build clone_repo build_repo submodule lib_make lib_clean lib_fclean
