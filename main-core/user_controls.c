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
	data->map[data->player_y][data->player_x].type = '0';
	refresh_cell(data, data->player_x, data->player_y);
	win_width = data->cell_size * data->map_width;
	win_height = data->cell_size * data->map_height;
	message = "You won !";
	x_position = (win_width - strlen(message) * (70 / 2)) / 2;
	y_position = (win_height - 50) / 2;
	print_message(data, message, x_position, y_position);
	message = "Press ESC";
	x_position = (win_width - strlen(message) * (70 / 2)) / 2;
	y_position = (win_height + 150) / 2;
	print_message(data, message, x_position, y_position);
	data->exit_info.win = 1;
}

void	enemy_touched(t_mlx_data *data)
/*
	This function handle the collision between the player and the enemies
*/
{
	int win_width;
	int	win_height;
	int x_position;
	int y_position;
	char	*message;

	data->map[data->player_y][data->player_x].type = '0';
	refresh_cell(data, data->player_x, data->player_y);
	win_width = data->cell_size * data->map_width;
	win_height = data->cell_size * data->map_height;
	message = "Wasted !";
	x_position = (win_width - strlen(message) * (70 / 2)) / 2;
	y_position = (win_height - 50) / 2;
	print_message(data, message, x_position, y_position);
	message = "Press ESC";
	x_position = (win_width - strlen(message) * (70 / 2)) / 2;
	y_position = (win_height + 150) / 2;
	print_message(data, message, x_position, y_position);
	data->exit_info.win = -1;
}

void	collect(t_mlx_data *data, int dest_x, int dest_y)
/*
	Create an exit for the player when he has collected all the items
	Increase the score
*/
{
	data->score++;
	if (data->collectible_count == data->score)
	{
		data->exit_info.exit_visibility = 1;
		refresh_cell(data, data->exit_info.exit_x, data->exit_info.exit_y);
	}
	data->map[data->player_y][data->player_x].type = '0';
	refresh_cell(data, data->player_x, data->player_y);
	data->player_x = dest_x;
	data->player_y = dest_y;
	data->map[data->player_y][data->player_x].type = 'P';
	refresh_cell(data, data->player_x, data->player_y);
}

void	player_move(t_mlx_data *data, int dest_x, int dest_y)
/*
	This function move the player in the data and update display
*/
{
	char	*message;
	int	x;

	message = "";
	if (data->map[dest_y][dest_x].type != '1' && data->exit_info.win == 0)
	{	
		data->move_count++;
		if (data->map[dest_y][dest_x].type == 'C')
			collect(data, dest_x, dest_y);
		else if (data->map[dest_y][dest_x].type == 'D')
			enemy_touched(data);
		else if ((data->map[dest_y][dest_x].type == 'E') && (data->exit_info.exit_visibility == 1))
			player_win(data);
		else
		{
			data->map[data->player_y][data->player_x].type = '0';
			refresh_cell(data, data->player_x, data->player_y);
			data->player_x = dest_x;
			data->player_y = dest_y;
			data->map[data->player_y][data->player_x].type = 'P';
			refresh_cell(data, data->player_x, data->player_y);
		}
		message = ft_strjoin("Movements : ", ft_itoa(data->move_count));
		x = (data->map_width / 2) + 6;
		while (x < data->map_width)
		{
			refresh_cell(data, x, data->map_height - 1);
			x++;
		}
		print_message(data, message, ((data->cell_size * data->map_width) / 2 - 50), (data->cell_size * data->map_height - 5));
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
	else if (keysym == XK_w || keysym == XK_Up)
		dest_y -= 1;
	else if (keysym == XK_s || keysym == XK_Down)
		dest_y += 1;
	else if (keysym == XK_a || keysym == XK_Left)
		dest_x -= 1;
	else if (keysym == XK_d || keysym == XK_Right)
		dest_x += 1;
	if (dest_x != data->player_x || dest_y != data->player_y)
		player_move(data, dest_x, dest_y);
	return (0);
}