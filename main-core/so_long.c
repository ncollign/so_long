/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:11:21 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 11:18:57 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_read(t_mlx_data *data, const char *map_path)
/*
	This function reads the fd containing the map
	and creates a 2D table with the map
*/
{
	char	*line;
	int		x;
	int		y;
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		ft_printf("Error\nMap file could not be opened.\n");
		return (-1);
	}
	data->map = (Tile **)malloc(data->map_height * sizeof(Tile *));
	if (!data->map)
	{
		ft_printf("Error\nMemory allocation failed!\n");
		close(map_fd);
		return (-1);
	}
	y = 0;
	while ((line = get_next_line(map_fd)) != NULL && y < data->map_height)
	{
		data->map[y] = (Tile *)malloc(data->map_width * sizeof(Tile));
		if (!data->map[y])
		{
			ft_printf("Error\nMemory allocation failed!\n");
			ft_free(&line);
			close(map_fd);
			return (-1);
		}

		x = 0;
		while (x < data->map_width && line[x] != '\0')
		{
			data->map[y][x].type = line[x];
			x++;
		}

		ft_free(&line);
		y++;
	}
	close(map_fd);
	return (0);
}

int handle_close(t_mlx_data *data)
{
    exit_game(data, 1);
    return (0);
}

void init_game(t_mlx_data *data)
/* This function initialize the game */
{
    if (!data)
	{
		ft_printf("Error\nData is not defined\n");
		exit_game(data, 1);
	}
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_printf("Error\nFailed to initialize MinilibX\n");
		exit_game(data, 1);
	}
	data->cell_size = 64;
	data->move_count = 0;
	data->score = 0;
	data->collectible_count = 0;
	data->exit_info.exit_visibility = 0;
	data->exit_info.win = 0;
	init_display(data);
}

int	main(int argc, char *argv[])
/* Main function */
{
	char	*map_path;
	t_mlx_data *data;

	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
    if (!data)
		return (EXIT_FAILURE);
	if (argc < 2)
	{
		map_path = "../maps/map_default.ber";
		ft_printf("No map path given. Default settings applied.\n");
	}
	else
	{
		map_path = ft_strjoin("../maps/", argv[1]);
		if (check_map_path(map_path))
				ft_printf("Map path saved.\n");
		else
		{
			map_path = "../maps/map_default.ber";
			ft_printf("Map path doesn't exist. Default settings applied.\n");
		}
	}
	get_map_size(data, map_path);
	map_read(data, map_path);
	init_game(data);
	check_map(data);
	render_map(data);
	mlx_key_hook(data->win_ptr, (int (*)())handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, (int (*)())handle_close, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}