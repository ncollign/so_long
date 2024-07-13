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

#include "../so_long.h"

static void	handle_error(char *message, t_mlx_data *data)
/*
	This function prints an error message and exit the game
*/
{
	ft_printf("Error\n%s", message);
	exit_game(data, 1);
}

static int	read_map(char *line, t_mlx_data *data)
/*
	This function reads all the file of the map to get the y value
*/
{
	int	x_len;
	int	y;

	y = 0;
	while (line != NULL)
	{
		y++;
		x_len = (int)(ft_strlen(line) - 2);
		if (x_len != x)
		{
			line = get_next_line(map_fd);
			if (line != NULL || (x_len != x - 2 && line == NULL))
			{
				ft_free(&line);
				handle_error("The map must be rectangular\n", data);
			}
		}
		line = get_next_line(map_fd);
	}
	return (y);
}

void	get_map_size(t_mlx_data *data, const char *map_path)
/*
	This function gives the size of the map
*/
{
	char	*line;
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		handle_error("Map file could not be opened.\n", data);
	line = get_next_line(map_fd);
	if (line == NULL)
	{
		ft_free(&line);
		close(map_fd);
		handle_error("Map file is empty or could not be read.\n", data);
	}
	data->map_width = ft_strlen(line) - 2;
	data->map_height = read_map(&line, data);
	ft_free(&line);
	close(map_fd);
	if (data->map_height < 4 || data->map_width < 4)
		handle_error("The map is too small.\n", data);
}
