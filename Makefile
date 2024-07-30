CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
MLX = -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lXext -lX11 -lm
SRC_DIR = main-core
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC_FILES:.c=.o)
NAME = so_long

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
