CC= gcc

CFLAGS+= -Wall -Wextra -Werror

SRC=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_split.c ft_strcmp.c ft_2dstrlen.c ft_strjoin_free.c

BNS=ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c \
	ft_lstiter.c

NAME= libft.a

OBJECTS = $(SRC:.c=.o)
BONUS_OBJ = $(BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rc libft.a $(OBJECTS) libft.h

%.o: %.c
	@$(CC) $< -c $(CFLAGS) -o $@

clean:
	@rm -f $(OBJECTS)
	@rm -f $(BONUS_OBJ)

fclean:
	@rm -f $(NAME)

re:	fclean all

.PHONY:
	clean fclean re

bonus:
	@$(CC) $(CFLAGS) -c $(BNS)
	@ar r $(NAME) $(BONUS_OBJ)
