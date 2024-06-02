#include "so_long.h"

int	player_win(t_mlx_data *data)
{
	if (data->collectible_count == data->score)
	{
		ft_printf("Congratulations ! You won !\n");
		return (0);
	}
	else
	{
		ft_printf("You need to collect all the items before exit :(\n");
		return (1);
	}
}

void	player_move(t_mlx_data *data, int dest_x, int dest_y)
/*
	This function move the player in the data and update display
	Increase score if the player hits a collectible
*/
{
	if (data->map[dest_y][dest_x].type != '1' && data->map[dest_y][dest_x].type != 'E')
	{
		if (data->map[dest_y][dest_x].type == 'C')
			data->score++;
		data->map[data->player_y][data->player_x].type = '0';
		refresh_cell(data, data->player_x, data->player_y);
		data->player_x = dest_x;
        data->player_y = dest_y;
        data->map[data->player_y][data->player_x].type = 'P';
        refresh_cell(data, data->player_x, data->player_y);
		data->move_count++;
	}
	if ((data->map[dest_y][dest_x].type == 'E') && (player_win(data) == 0))
			exit_game(data);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	int	dest_y;
	int	dest_x;

	dest_y = data->player_y;
	dest_x = data->player_x;
	if (keysym == XK_Escape)
		exit_game(data);
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
		dest_x += 1;
	}
	if (dest_x != data->player_x || dest_y != data->player_y)
		player_move(data, dest_x, dest_y);
	return (0);
}