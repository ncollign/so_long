/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:44:56 by ncollign          #+#    #+#             */
/*   Updated: 2024/07/09 11:44:57 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_map(t_mlx_data *data, int map_fd)
/*
	This function allocates each line of the map in data
	Define the type of each tile
*/
{
	char	*line;
	int		y;
	int		x;

	y = 0;
	while (y < data->map_height || line != NULL)
	{
		line = get_next_line(map_fd);
		data->map[y] = (t_tile *)malloc(data->map_width * sizeof(t_tile));
		if (!data->map[y])
		{
			ft_printf("Error\nMemory allocation failed!\n");
			ft_free(&line);
			close(map_fd);
			exit(EXIT_FAILURE);
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
}

static void	initialize_map(t_mlx_data *data, const char *map_path)
/*
	This function reads the fd containing the map and
	creates a 2D table with the map
*/
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		ft_printf("Error\nMap file could not be opened.\n");
		exit(EXIT_FAILURE);
	}
	data->map = (t_tile **)malloc(data->map_height * sizeof(t_tile *));
	if (!data->map)
	{
		ft_printf("Error\nMemory allocation failed!\n");
		close(map_fd);
		exit(EXIT_FAILURE);
	}
	set_map(data, map_fd);
	close(map_fd);
}

static int	handle_close(t_mlx_data *data)
/*
	This function handles closing when clicking on the cross in the corner of
	the window.
*/
{
	exit_game(data, 1);
	return (0);
}

static char	*define_path(int argc, char *argv)
{
	char	*map_path;
	char	*full_path;

	if (argc < 2)
	{
		map_path = "maps/map_default.ber";
		ft_printf("No map path given. Default settings applied.\n");
	}
	else
	{
		full_path = ft_strjoin("maps/", argv);
		map_path = full_path;
		ft_free(&full_path);
		if (check_map_path(map_path))
			ft_printf("Map path saved.\n");
		else
		{
			map_path = "maps/map_default.ber";
			ft_printf("Map path doesn't exist. Default settings applied.\n");
		}
	}
	return (map_path);
}

int	main(int argc, char *argv[])
/*
	Main function
	Call all the functions to initialize the game
*/
{
	t_mlx_data	*data;
	char		*map_path;

	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	if (!data)
		return (EXIT_FAILURE);
	map_path = define_path(argc, argv[1]);
	get_map_size(data, map_path);
	initialize_map(data, map_path);
	init_game(data);
	check_map(data);
	render_map(data);
	mlx_key_hook(data->win_ptr, (int (*)())handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, (int (*)())handle_close, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
