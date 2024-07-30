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

void	test_tile(t_mlx_data *data, int x_tested,
			int y_tested, int has_path[2]);

void	flood_fill(t_mlx_data *data, int x, int y, int has_path[2])
/*
	This function tests all the tiles around the player and if he can walk on it
	Calls the function test_tile if OK
*/
{
	if (data->map[y][x - 1].type == '0' || data->map[y][x - 1].type == 'C'
			|| data->map[y][x - 1].type == 'E')
		test_tile(data, x - 1, y, has_path);
	if (data->map[y][x + 1].type == '0' || data->map[y][x + 1].type == 'C'
			|| data->map[y][x + 1].type == 'E')
		test_tile(data, x + 1, y, has_path);
	if (data->map[y - 1][x].type == '0' || data->map[y - 1][x].type == 'C'
			|| data->map[y - 1][x].type == 'E')
		test_tile(data, x, y - 1, has_path);
	if (data->map[y + 1][x].type == '0' || data->map[y + 1][x].type == 'C'
			|| data->map[y + 1][x].type == 'E')
		test_tile(data, x, y + 1, has_path);
}

void	test_tile(t_mlx_data *data, int x_tested, int y_tested, int has_path[2])
/*
	This function tests a tile if it is a Collectible or an exit or nothing
	If the player cant walk on it, the type become 'T' has tested
	The floodfill algorithm replace all the map to test all the tiles one time
	Call the function flood_fill again to test recursively the Tiles the player
	can walk on it
*/
{
	if (data->map[y_tested][x_tested].type == 'C')
		has_path[0]++;
	else if (data->map[y_tested][x_tested].type == 'E')
		has_path[1]++;
	data->map[data->player_y][data->player_x].type = 'T';
	data->player_x = x_tested;
	data->player_y = y_tested;
	flood_fill(data, data->player_x, data->player_y, has_path);
}

t_tile	**copy_map(t_tile **map, int width, int height)
{
	t_tile	**new_map;
	int		i;
	int		j;

	new_map = (t_tile **)malloc(sizeof(t_tile *) * height);
	if (!new_map)
		return (NULL);
	for (i = 0; i < height; i++)
	{
		new_map[i] = (t_tile *)malloc(sizeof(t_tile) * width);
		if (!new_map[i])
		{
			while (--i >= 0)
				free(new_map[i]);
			free(new_map);
			return (NULL);
		}
		for (j = 0; j < width; j++)
		{
			new_map[i][j] = map[i][j];
		}
	}
	return (new_map);
}

void	restore_map(t_tile **map, t_tile **backup, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			map[y][x] = backup[y][x];
			x++;
		}
		y++;
	}
}

void	verify_player_path(t_mlx_data *data)
/*
	This function verify that the player can move on the map
	has_path :
	[0] : Collected_counter
	[1] : Exit_finder

	player_coords :
	[0] : x
	[1] : y
*/
{
	t_tile	**map_backup;
	int		has_path[2];
	int		player_coords[2];

	map_backup = copy_map(data->map, data->map_width, data->map_height);
	if (!map_backup)
	{
		ft_printf("Error\nMemory allocation failed\n");
		exit_game(data, 1);
	}
	player_coords[0] = data->player_x;
	player_coords[1] = data->player_y;
	has_path[0] = 0;
	has_path[1] = 0;
	flood_fill(data, data->player_x, data->player_y, has_path);
	if (has_path[0] != data->collectible_count || !has_path[1])
	{
		ft_printf("Error\nImpossible to finish this map\n");
		exit_game(data, 1);
	}
	restore_map(data->map, map_backup, data->map_width, data->map_height);
	data->player_x = player_coords[0];
	data->player_y = player_coords[1];
	free_map(map_backup, data->map_height);
}
