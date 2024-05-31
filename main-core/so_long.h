#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx_linux/mlx.h"

typedef	struct
{
	char	type;
}	Tile;

typedef struct  s_img
{
    void        *img_ptr;
    char        *data;
    int         width;
    int         height;
    int         bpp;
    int         size_line;
    int         endian;
}	t_img;

typedef struct  s_mlx_data
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_img       *background;
    t_img       *walls;
    t_img       *collectibles;
    t_img       *player;
    t_img       *exit;
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

int	getMapSize(t_mlx_data *data, const char *map_path);
int	checkMapPath(char *map_path);
int	checkMap(t_mlx_data *data);
int	handle_input(int keysym, t_mlx_data *data);
void render_map(t_mlx_data *data);
void refresh_cell(t_mlx_data *mlx_data, int x, int y);
t_img *resize_image(void *mlx_ptr, t_img *src_img, int new_width, int new_height);
t_img	*load_image(void *mlx_ptr, char *path);
void	exit_game(t_mlx_data *data);

#endif

