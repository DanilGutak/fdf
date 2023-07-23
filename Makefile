# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux 
LDFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

# Project name and source files
NAME = fdf
SRCS = main.c read.c get_next_line_utils.c get_next_line.c

# Object files and dependencies
OBJS = $(SRCS:.c=.o)

# Rule to build the project
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) -g
# Rule to compile source files into object files
.c.o:
	cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./include

# Rule to clean object files
clean:
	rm -f $(OBJS)

# Rule to clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rule to recompile everything
re: fclean all

.PHONY: all clean fclean re
