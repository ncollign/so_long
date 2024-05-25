SRCS = $(shell find . -type f -name '*.c')
OBJS = $(SRCS:.c=.o)
MLXFLAG = -lmlx -lXext -lX11
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra $(MLXFLAG) -I ./

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
