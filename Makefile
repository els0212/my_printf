SRC=ft_printf.c
OBJ=$(SRCS:.c=.o)
NAME=libftprintf.a
INC=.
CC=gcc
CFLAGS=-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.c.o : $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
