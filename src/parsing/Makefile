NAME := test

CC := cc
CFLAGS := -Wextra -Wall -Werror -fsanitize=address
LDFLAGS := -fsanitize=address

SRCDIR := .
SOURCES := colors.c map.c read_file.c textures.c free.c ft_validate_input.c
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
