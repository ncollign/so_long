#include "so_long.h"

void	exit_game(t_mlx_data *data, int	error_catch)
{
	int		y;

	ft_printf("Closing the window...\n");
	if (data->map != NULL)
	{
		y = 0;
		while (y < data->map_height)
		{
			free(data->map[y]);
			y++;
		}
		free(data->map);
	}
	if (data->background != NULL)
		mlx_destroy_image(data->mlx_ptr, data->background->image);
	if (data->walls != NULL)
		mlx_destroy_image(data->mlx_ptr, data->walls->image);
	if (data->collectibles != NULL)
		mlx_destroy_image(data->mlx_ptr, data->collectibles->image);
	if (data->player != NULL)
		mlx_destroy_image(data->mlx_ptr, data->player->image);
	if (data->exit != NULL)
		mlx_destroy_image(data->mlx_ptr, data->exit->image);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit (error_catch);
}