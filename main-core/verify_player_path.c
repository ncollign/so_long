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

static void	test_tile(t_mlx_data *data, int x_tested,
				int y_tested, int has_path[2]);

static void	flood_fill(t_mlx_data *data, int x, int y, int has_path[2])
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

static void	test_tile(t_mlx_data *data, int x_tested,
		int y_tested, int has_path[2])
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

static t_tile	**copy_map(t_tile **map, int width, int height)
/*
	This function copies the map to create a save, before the floodfill
*/
{
	t_tile	**new_map;
	int		x;
	int		y;

	new_map = (t_tile **)malloc(sizeof(t_tile *) * height);
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_map[y] = (t_tile *)malloc(sizeof(t_tile) * width);
		if (!new_map[y])
		{
			free_map(new_map, height);
			return (NULL);
		}
		x = 0;
		while (x < width)
		{
			new_map[y][x] = map[y][x];
			x++;
		}
		y++;
	}
	return (new_map);
}

static void	restore_map(t_tile **map, t_tile **backup, int width, int height)
/*
	This function restore the map after the floodfill
*/
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
