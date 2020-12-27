SRC=ft_printf.c ft_printf_format_utils.c ft_printf_str_utils.c ft_printf_conv.c ft_printf_mem_utils.c
OBJ=$(SRC:.c=.o)
NAME=libftprintf.a
CC=gcc
AR=ar
ARFLAGS=rcs
CFLAGS=-Wall -Wextra -Werror

all : $(NAME)

.c.o : $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
