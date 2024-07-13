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

static void	verify_player_path(t_mlx_data *data)
/*
	This function verify that the player can move on the map
*/
{
	int	x;
	int	y;
	int	has_path;

	has_path = 0;
	x = data->player_x;
	y = data->player_y;
	if (x > 0 && data->map[y][x - 1].type == '0')
		has_path = 1;
	if (x < data->map_width - 1 && data->map[y][x + 1].type == '0')
		has_path = 1;
	if (y > 0 && data->map[y - 1][x].type == '0')
		has_path = 1;
	if (y < data->map_height - 1 && data->map[y + 1][x].type == '0')
		has_path = 1;
	if (!has_path)
	{
		ft_printf("Error\nThe player must be able to move at start.\n");
		exit_game(data, 1);
	}
}

static void	

void	check_map(t_mlx_data *data)
/*
	This function checks if the map is OK and have all the specifications in the subject
	Returns 0 if OK
	Returns 1 if NOK
*/
{
	int	x;
	int	y;
	int	has_player;
	int	has_exit;

	has_exit = 0;
	has_player = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((x == 0) || (x == data->map_width - 1))
				if (data->map[y][x].type != '1')
					handle_error("The map not closed not rectangular\n", data);
			if ((y == 0) || (y == data->map_height - 1))
				if (data->map[y][x].type != '1')
					handle_error("The map not closed not rectangular\n", data);
			if (data->map[y][x].type == 'C')
				data->collectible_count++;
			else if (data->map[y][x].type == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				has_player++;
			}
			else if (data->map[y][x].type == 'E')
			{
				data->exit_info.exit_x = x;
				data->exit_info.exit_y = y;
				has_exit++;
			}
			x++;
		}
		y++;
	}
	if (data->collectible_count == 0)
		handle_error("The map must have minimum 1 item to collect\n", data);
	if ((has_player == 0) || (has_player > 1))
		handle_error("The map must have 1 player\n", data);
	if ((has_exit == 0) || (has_exit > 1))
		handle_error("The map must have 1 exit\n", data);
	verify_player_path(data);
}

int	check_map_path(char *map_path)
/* This function verify that the fd is a .ber and if it exists */
{
	int	map_fd;

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
