# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 11:23:35 by lzipp             #+#    #+#              #
#    Updated: 2024/06/14 11:25:23 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

CC := g++
CCFLAGS := -Wextra -Wall -Werror

SRCDIR := ./src
SOURCES := $(addprefix $(SRCDIR)/, main.c Animal.c Dog.c Cat.c)
OBJDIR = ./obj
OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: all clean fclean re
