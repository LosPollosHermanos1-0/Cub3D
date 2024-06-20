NAME := test

CC := g++
CCFLAGS := -Wextra -Wall -Werror -fsanitize=address

SOURCES := colors.c helpers.c map.c read_file.c textures.c free.c
SOURCES += $(addprefix ../../libft/src/, *.c)
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
