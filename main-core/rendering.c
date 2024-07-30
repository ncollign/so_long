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

void	print_message(t_mlx_data *data, char *message, int x, int y)
/*
	This function displays a message on the screen
*/
{
	mlx_set_font(data->mlx_ptr, data->win_ptr,
		"-*-times-*-*-*-*-80-*-*-*-*-*-*-*");
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, 0xFFFFFF, message);
}

void	refresh_display_player_moves(t_mlx_data *data)
/*
	This function refreshes de display of the movement counter of the player
*/
{
	char	*message;
	char	*moves;
	int		x;

	moves = ft_itoa(data->move_count);
	message = ft_strjoin("Movements : ", moves);
	x = (data->map_width / 2) + 6;
	while (x < data->map_width)
	{
		refresh_cell(data, x, data->map_height - 1);
		x++;
	}
	print_message(data, message, ((data->cell_size * data->map_width)
			/ 2 - 50), (data->cell_size * data->map_height - 5));
	ft_free(&message);
	ft_free(&moves);
}

t_img	*resize_image(void *mlx_ptr, t_img *src_img,
		int new_width, int new_height)
/*
	This function resizes the image and displays the right size on the window
*/
{
	t_img	*new_img;
	int		x;
	int		y;

	new_img = create_image(mlx_ptr, new_width, new_height);
	if (!new_img)
		return (NULL);
	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			*(int *)(new_img->data + (y * new_img->size_line + x
						* (new_img->bpp / 8))) = *(int *)(src_img->data
					+ ((int)(y * ((double)src_img->width / new_width))
						*src_img->size_line + (int)(x * (double)src_img->height
							/ new_height)*(src_img->bpp / 8)));
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx_ptr, src_img->image);
	free(src_img);
	return (new_img);
}

void	refresh_cell(t_mlx_data *data, int x, int y)
/*
	This function refreshes a cell on the display
*/
{
	if (data->map[y][x].type == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->walls->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->collectibles->image, x * data->cell_size, y
			* data->cell_size);
	else if (data->map[y][x].type == 'P' && (data->player_x % 2 == 0))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player1->image, x * data->cell_size, y
			* data->cell_size);
	else if (data->map[y][x].type == 'P' && (data->player_x % 2 != 0))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player2->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'D')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->enemy->image, x * data->cell_size, y * data->cell_size);
	else if (data->map[y][x].type == 'E'
		&& data->exit_info.exit_visibility == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->exit->image, x * data->cell_size, y * data->cell_size);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->background->image, x * data->cell_size, y * data->cell_size);
}

void	render_map(t_mlx_data *data)
/*
	This function renders the map
*/
{
	char	*message;
	char	*nbr_move;
	int		x;
	int		y;

	message = "";
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			refresh_cell(data, x, y);
			x++;
		}
		y++;
	}
	nbr_move = ft_itoa(data->move_count);
	message = ft_strjoin("Movements : ", nbr_move);
	print_message(data, message, ((data->cell_size * data->map_width) / 2 - 50),
		(data->cell_size * data->map_height - 5));
	ft_free(&nbr_move);
	ft_free(&message);
}
