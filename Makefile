# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 17:56:59 by dgutak            #+#    #+#              #
#    Updated: 2023/07/31 17:57:03 by dgutak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux 
LDFLAGS = -Lminilibx-linux -L./libft  -lmlx -lXext -lX11 -lm -lft


NAME = fdf
LIBFT	=	./libft/libft.a
SRCS = main.c read.c get_next_line_utils.c get_next_line.c draw.c utils.c error.c transform.c


OBJS = $(SRCS:.c=.o)


all: $(NAME)
	rm -f $(OBJS)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS) $(LDFLAGS)

.c.o:
	cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./include


clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
