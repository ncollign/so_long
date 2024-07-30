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
	free(data);
	exit(EXIT_FAILURE);
}

static int	get_width(char **line, int map_fd, t_mlx_data *data)
/*
	This function reads all the file of the map to get the y value
*/
{
	int	y;

	y = 0;
	while (*line != NULL)
	{
		y++;
		if ((int)(ft_strlen(*line) - 2) != data->map_width)
		{
			ft_free(line);
			*line = get_next_line(map_fd);
			if (*line != NULL)
			{
				ft_free(line);
				close(map_fd);
				handle_error("The map must be rectangular\n", data);
			}
		}
		else
		{
			ft_free(line);
			*line = get_next_line(map_fd);
		}
	}
	ft_free(line);
	return (y);
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
		handle_error("Map file could not be opened.\n", data);
	line = get_next_line(map_fd);
	if (line == NULL)
	{
		ft_free(&line);
		close(map_fd);
		handle_error("Map file is empty or could not be read.\n", data);
	}
	data->map_width = ft_strlen(line) - 2;
	data->map_height = get_width(&line, map_fd, data);
	ft_free(&line);
	close(map_fd);
	if (data->map_height < 4 || data->map_width < 4)
		handle_error("The map is too small.\n", data);
}
