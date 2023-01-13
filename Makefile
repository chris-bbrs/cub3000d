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
		hook/key_hooks.c \
		raycast/movement.c raycast/rotation.c raycast/raycasting.c raycast/raycast_utils.c \
		initiate/init.c initiate/player.c \
		utils/utils.c utils/exit_funcs.c \
		parser/parsing_utils.c parser/check_map.c parser/parsing.c \

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@

$(NAME): $(OBJ) $(GNL) $(LIBFT) ./include/cub3d.h
	gcc $(FLAGS) $(OBJ) $(GNL) $(LIBFT) MLX42/libmlx42.a MLX42/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -f ps

fclean:
	make clean
	rm -f $(NAME)

re: fclean all
