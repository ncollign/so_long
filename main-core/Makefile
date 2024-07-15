NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/X11/include -I../libft
MLX = -L../minilibx-linux -lmlx -L/opt/X11/lib -lXext -lX11 -lm
SRCS = so_long.c rendering.c user_controls.c check_map.c memory_management.c utils/check_map.c
LIBFT = ../libft/libft.a
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT)

$(LIBFT):
	make -C ../libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
