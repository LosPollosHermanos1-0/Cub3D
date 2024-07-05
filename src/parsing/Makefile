NAME := test

CC := cc
CFLAGS := -Wextra -Wall -Werror -fsanitize=address
LDFLAGS := -fsanitize=address

SRCDIR := .
SOURCES := free.c ft_validate_input.c load_data.c map_utility.c map.c rgb.c textures_rgb.c textures.c validate_map.c
OBJDIR = ./obj
OBJECTS := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(NAME) -L. ../../libft/libft.a

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
