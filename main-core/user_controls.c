#include "so_long.h"

void	player_move(t_mlx_data *data, int dest_x, int dest_y)
{
	if (data->map[dest_x][dest_y].type != '1')
	{
		ft_printf("OK");
		data->map[data->player_y][data->player_x].type = '0';
		refresh_cell(data, data->player_x, data->player_y);

		data->player_x = dest_x;
        data->player_y = dest_y;
        data->map[data->player_y][data->player_x].type = 'P';
        refresh_cell(data, data->player_x, data->player_y);
	}
}

int	handle_input(int keysym, t_mlx_data *data)
{
	int	dest_y;
	int	dest_x;

	dest_y = data->player_y;
	dest_x = data->player_x;
	if (keysym == XK_Escape)
	{
		ft_printf("Closing the window...");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	else if (keysym == XK_Up)
	{
		ft_printf("HAUT\n");
		dest_y -= 1;
	}
	else if (keysym == XK_Down)
	{
		ft_printf("BAS\n");
		dest_y += 1;
	}
	else if (keysym == XK_Left)
	{
		ft_printf("GAUCHE\n");
		dest_x -= 1;
	}
	else if (keysym == XK_Right)
	{
		ft_printf("DROITE\n");
		dest_y += 1;
	}
	if (dest_x != data->player_x || dest_y != data->player_y)
		player_move(data, dest_x, dest_y);
	return (0);
}