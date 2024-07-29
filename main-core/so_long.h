#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
//# include "../minilibx-linux/mlx.h"
//# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef	struct	s_Tile
{
	char	type;
}	Tile;

typedef	struct	s_exit_info
{
	int		exit_visibility;
	int		exit_x;
	int		exit_y;
	int		win;
}	t_exit_info;

typedef struct  s_mlx_data
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_img       *background;
    t_img       *walls;
    t_img       *collectibles;
    t_img       *player1;
	t_img		*player2;
    t_img       *exit;
	t_img		*enemy;
	t_exit_info	exit_info;
    int         map_width;
    int         map_height;
    int         cell_size;
	int         player_x;
    int         player_y;
    Tile        **map;
    int         move_count;
	int			collectible_count;
	int			score;
}	t_mlx_data;

void	getMapSize(t_mlx_data *data, const char *map_path);
int	checkMapPath(char *map_path);
void	checkMap(t_mlx_data *data);
int	handle_input(int keysym, t_mlx_data *data);
void render_map(t_mlx_data *data);
void refresh_cell(t_mlx_data *mlx_data, int x, int y);
t_img *resize_image(void *mlx_ptr, t_img *src_img, int new_width, int new_height);
t_img	*load_image(void *mlx_ptr, char *path);
void	exit_game(t_mlx_data *data, int error_catch);
t_img *create_image(void *mlx_ptr, int width, int height);
void	print_message(t_mlx_data *data, char	*message, int x, int y);
void	init_display(t_mlx_data *data);
void	refresh_movement_count(t_mlx_data *data);

#endif

