#include "so_long.h"

void	player_win(t_mlx_data *data)
/*
	Display the win title
*/
{
	int win_width;
	int	win_height;
	int x_position;
	int y_position;
	char	*message;

	message = "";
	if (data->collectible_count == data->score)
	{
		win_width = data->cell_size * data->map_width;
		win_height = data->cell_size * data->map_height;
		message = "You won !";
		x_position = (win_width - strlen(message) * (70 / 2)) / 2;
		y_position = (win_height - 50) / 2;
		print_message(data, message, x_position, y_position);
		message = ft_strjoin("Movements count : ", ft_itoa(data->move_count));
		x_position = (win_width - strlen(message) * (70 / 2)) / 2;
		y_position = (win_height + 150) / 2;
		print_message(data, message, x_position, y_position);
		data->exit_info.win = 1;
	}
}

void	exit_appear(t_mlx_data *data)
/*
	Create an exit for the player when he has collected all the items
*/
{
	if (data->collectible_count == data->score)
	{
		data->exit_info.exit_visibility = 1;
		refresh_cell(data, data->exit_info.exit_x, data->exit_info.exit_y);
	}
}

void	player_move(t_mlx_data *data, int dest_x, int dest_y)
/*
	This function move the player in the data and update display
	Increase score if the player hits a collectible
*/
{
	if (data->map[dest_y][dest_x].type != '1' && data->exit_info.win == 0)
	{	
		if (data->map[dest_y][dest_x].type == 'C')
		{
			data->score++;
			exit_appear(data);
		}
		data->move_count++;
		if ((data->map[dest_y][dest_x].type == 'E') && (data->exit_info.exit_visibility == 1))
			player_win(data);

		data->map[data->player_y][data->player_x].type = '0';
		refresh_cell(data, data->player_x, data->player_y);
		data->player_x = dest_x;
        data->player_y = dest_y;
        data->map[data->player_y][data->player_x].type = 'P';
        refresh_cell(data, data->player_x, data->player_y);
	}
}

int	handle_input(int keysym, t_mlx_data *data)
/*
	Handle all the inputs of the user
*/
{
	int	dest_y;
	int	dest_x;

	dest_y = data->player_y;
	dest_x = data->player_x;
	if (keysym == XK_Escape)
		exit_game(data, 1);
	else if (keysym == XK_Up)
		dest_y -= 1;
	else if (keysym == XK_Down)
		dest_y += 1;
	else if (keysym == XK_Left)
		dest_x -= 1;
	else if (keysym == XK_Right)
		dest_x += 1;
	if (dest_x != data->player_x || dest_y != data->player_y)
		player_move(data, dest_x, dest_y);
	return (0);
}