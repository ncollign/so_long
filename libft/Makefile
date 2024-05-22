SRCS = $(wildcard *.c) \
       $(wildcard ft_printf/*.c) \
       $(wildcard get_next_line/*.c)
OBJS = $(SRCS:.c=.o)
NAME = libft.a
CC = clang
CFLAGS = -Wall -Werror -Wextra -I ./

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
