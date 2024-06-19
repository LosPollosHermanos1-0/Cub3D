# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vscode <vscode@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 11:23:35 by lzipp             #+#    #+#              #
#    Updated: 2024/06/19 09:45:58 by vscode           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

CC := g++
CCFLAGS := -Wextra -Wall -Werror

SRCDIR := ./src
SOURCES := $(addprefix $(SRCDIR)/, main.c Animal.c Dog.c Cat.c)
OBJDIR = ./obj
OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

all: submodule $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

submodule:
	@if git submodule status libft | grep -q '^-' ; then \
		echo "Submodule directory does not exist. Initializing and updating submodules..."; \
		git submodule update --init --recursive; \
	else \
		echo "Submodule directory exists. Skipping initialization."; \
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: all clean fclean re
