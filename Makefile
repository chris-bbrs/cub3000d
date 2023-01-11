# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 16:37:50 by gjupy             #+#    #+#              #
#    Updated: 2023/01/04 16:37:50 by gjupy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = 	cub3d
GNL = 	Get_next_line/gnl.a
LIBFT = libft/libft.a

SRC = 	main.c \
		parsing.c \
		exit_funcs.c \
		check_map.c \
		player.c \
		key_hooks.c \
		movement.c rotation.c \
		init.c \
		raycasting.c \
		utils.c \
		parsing_utils.c \
		raycast_utils.c

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@

$(NAME): $(OBJ) $(GNL) $(LIBFT) cub3d.h
	gcc $(FLAGS) $(OBJ) $(GNL) $(LIBFT) MLX42/libmlx42.a MLX42/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all
