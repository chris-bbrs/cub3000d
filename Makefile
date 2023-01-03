FLAGS = -Wall -Wextra -Werror
NAME = cub3d
GNL = Get_next_line/gnl.a
LIBFT = libft/libft.a
SRC = main.c parsing.c exit_funcs.c check_map.c

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

valgrind: re
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

re: fclean all
