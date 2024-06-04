#include "so_long.h"

void	print_message(t_mlx_data *data, char *message, int x, int y)
/*
	This function displays a message on the screen
*/
{
	mlx_set_font(data->mlx_ptr, data->win_ptr, "-*-times-*-*-*-*-80-*-*-*-*-*-*-*");
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFFFFFF, message);
}

t_img	*resize_image(void *mlx_ptr, t_img *src_img, int new_width, int new_height)
/*
	This function resizes the image and displays the right size on the window
*/
{
	t_img *new_img = create_image(mlx_ptr, new_width, new_height);
	if (!new_img)
	return (NULL);

	double x_ratio = (double)src_img->width / new_width;
	double y_ratio = (double)src_img->height / new_height;
	for (int y = 0; y < new_height; y++)
	{
		for (int x = 0; x < new_width; x++)
		{
			int src_x = (int)(x * x_ratio);
			int src_y = (int)(y * y_ratio);
			int color = *(int *)(src_img->data + (src_y * src_img->size_line + src_x * (src_img->bpp / 8)));
			*(int *)(new_img->data + (y * new_img->size_line + x * (new_img->bpp / 8))) = color;
		}
	}
	return (new_img);
}

void	refresh_cell(t_mlx_data *data, int x, int y)
/*
	This function refreshes a cell on the display
*/
{
	if (data->map[y][x].type == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->walls->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collectibles->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'P' && (data->player_x % 2 == 0))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player1->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'P' && (data->player_x % 2 != 0))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player2->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'D')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'E' && data->exit_info.exit_visibility == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit->image, x * data->cell_size, y * data->cell_size);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background->image, x * data->cell_size, y * data->cell_size);
}

void	render_map(t_mlx_data *data)
/*
	This function renders the map
*/
{
	char	*message;
	int	x;
	int	y;

	message = "";
	for (y = 0; y < data->map_height; y++)
	{
		for (x = 0; x < data->map_width; x++)
		{
			refresh_cell(data, x, y);
		}
	}
	message = ft_strjoin("Movements : ", ft_itoa(data->move_count));
	print_message(data, message, ((data->cell_size * data->map_width) / 2 - 50), (data->cell_size * data->map_height - 5));
}