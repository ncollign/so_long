/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:44:11 by ncollign          #+#    #+#             */
/*   Updated: 2024/07/09 11:44:14 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_error(char *message, t_mlx_data *data)
/*
	This function prints an error message and exit the game
*/
{
	ft_printf("Error\n%s", message);
	exit_game(data, 1);
}

static void	count_each(int x, int y, int counter[2], t_mlx_data *data)
/*
	This function tests the type of the tile and count
	counter[0] : player_counter;
	counter[1] : exit_counter;
*/
{
	if ((x == 0) || (x == data->map_width - 1))
		if (data->map[y][x].type != '1')
			handle_error("Map not closed\n", data);
	if ((y == 0) || (y == data->map_height - 1))
		if (data->map[y][x].type != '1')
			handle_error("Map not closed\n", data);
	if (data->map[y][x].type == 'C')
		data->collectible_count++;
	else if (data->map[y][x].type == 'P')
	{
		data->player_x = x;
		data->player_y = y;
		counter[0]++;
	}
	else if (data->map[y][x].type == 'E')
	{
		data->exit_info.exit_x = x;
		data->exit_info.exit_y = y;
		counter[1]++;
	}
	else if (data->map[y][x].type != 'D' && data->map[y][x].type != '0'
				&& data->map[y][x].type != '1')
		handle_error("Wrong character in the map\n", data);
}

void	check_map(t_mlx_data *data)
/*
	This function checks if the map is OK and have all the specifications in the subject
	Returns 0 if OK
	Returns 1 if NOK
	counter[0] : player_counter;
	counter[1] : exit_counter;

*/
{
	int	x;
	int	y;
	int	counter[2];

	y = 0;
	counter[0] = 0;
	counter[1] = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			count_each(x, y, counter, data);
			x++;
		}
		y++;
	}
	if (data->collectible_count == 0)
		handle_error("The map must have minimum 1 item to collect\n", data);
	if ((counter[0] == 0) || (counter[0] > 1))
		handle_error("The map must have 1 player\n", data);
	if ((counter[1] == 0) || (counter[1] > 1))
		handle_error("The map must have 1 exit\n", data);
	verify_player_path(data);
}

int	check_map_path(char *map_path)
/* This function verify that the fd is a .ber and if it exists */
{
	int	map_fd;

	ft_printf("%s\n", map_path);
	if (ft_strnstr(map_path, ".ber", ft_strlen(map_path)))
	{
		map_fd = open(map_path, O_RDONLY);
		if (map_fd == -1)
		{
			close(map_fd);
			return (0);
		}
		else
		{
			close(map_fd);
			return (1);
		}
	}
	return (0);
}
