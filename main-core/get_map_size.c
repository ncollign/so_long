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

static void	handle_error(char *message, int map_fd, t_mlx_data *data)
/*
	This function prints an error message and exit the game
*/
{
	ft_printf("Error\n%s", message);
	free(data->map_path);
	free(data);
	if (map_fd > 0)
		close(map_fd);
	exit(EXIT_FAILURE);
}

static void	verify_line(int last_line, int map_fd, t_mlx_data *data)
/*
	This functions verifies if the wrong width is due to the last line
	Because there isn't any \n character.
	=> last_line = data->width - 1
*/
{
	char	*line;

	line = get_next_line(map_fd);
	if (line != NULL || last_line != data->map_width)
	{
		ft_free(&line);
		handle_error("The map must be rectangular\n", map_fd, data);
	}
	ft_free(&line);
}

static void	define_height(char **line, int map_fd, t_mlx_data *data)
/*
	This function reads all the file of the map to get the y value
*/
{
	int	last_line;

	while (*line != NULL)
	{
		data->map_height++;
		if ((int)(ft_strlen(*line)) - 1 != data->map_width)
		{
			last_line = (int)(ft_strlen(*line));
			ft_free(line);
			verify_line(last_line, map_fd, data);
		}
		else
		{
			last_line = (int)(ft_strlen(*line)) - 1;
			ft_free(line);
			*line = get_next_line(map_fd);
			if (last_line == data->map_width && *line == NULL)
			{
				ft_free(line);
				handle_error("The map must be rectangular\n", map_fd, data);
			}
		}
	}
}

void	get_map_size(t_mlx_data *data, char *map_path)
/*
	This function gives the size of the map
*/
{
	char	*line;
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		handle_error("Map file could not be opened.\n", map_fd, data);
	line = get_next_line(map_fd);
	if (line == NULL)
	{
		ft_free(&line);
		handle_error("Map file is empty or could not be read.\n", map_fd, data);
	}
	data->map_width = ft_strlen(line) - 1;
	data->map_height = 0;
	define_height(&line, map_fd, data);
	close(map_fd);
	if (data->map_height < 4 || data->map_width < 4)
		handle_error("The map is too small.\n", map_fd, data);
}
