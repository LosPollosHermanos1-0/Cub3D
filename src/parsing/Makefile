NAME := test

CC := g++
CCFLAGS := -Wextra -Wall -Werror -fsanitize=address

SOURCES := colors.c helpers.c map.c read_file.c textures.c
SOURCES += $(addprefix ../../libft/src/, *.c)
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