CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
NAME	= 	gnl.a
SRC		= 	get_next_line.c get_next_line_utils.c
OBJ		= 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $^ -o $@

$(NAME): $(OBJ)
	ar -rc $@ $^

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(NAME)

re: fclean all
