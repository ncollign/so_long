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

static void	init_resizing(t_mlx_data *data)
/*
	This function initialize the resizing of the images
*/
{
	data->background = resize_image(data->mlx_ptr, data->background,
			data->cell_size, data->cell_size);
	data->walls = resize_image(data->mlx_ptr, data->walls,
			data->cell_size, data->cell_size);
	data->collectibles = resize_image(data->mlx_ptr, data->collectibles,
			data->cell_size, data->cell_size);
	data->player1 = resize_image(data->mlx_ptr, data->player1,
			data->cell_size, data->cell_size);
	data->player2 = resize_image(data->mlx_ptr, data->player2,
			data->cell_size, data->cell_size);
	data->exit = resize_image(data->mlx_ptr, data->exit,
			data->cell_size, data->cell_size);
	data->enemy = resize_image(data->mlx_ptr, data->enemy,
			data->cell_size, data->cell_size);
}

static void	init_image_loading(t_mlx_data *data)
/*
	This function initialize the image loading into memory
*/
{
	data->background = load_image(data->mlx_ptr,
			"ressources/background_texture.xpm");
	data->walls = load_image(data->mlx_ptr,
			"ressources/wall_texture.xpm");
	data->collectibles = load_image(data->mlx_ptr,
			"ressources/collectible_texture.xpm");
	data->player1 = load_image(data->mlx_ptr,
			"ressources/player/player_texture1.xpm");
	data->player2 = load_image(data->mlx_ptr,
			"ressources/player/player_texture2.xpm");
	data->exit = load_image(data->mlx_ptr,
			"ressources/exit_texture.xpm");
	data->enemy = load_image(data->mlx_ptr,
			"ressources/enemy_texture.xpm");
	if ((data->background == NULL) || (data->walls == NULL)
		|| (data->collectibles == NULL) || (data->player1 == NULL)
		|| (data->player2 == NULL) || (data->exit == NULL)
		|| (data->enemy == NULL))
	{
		ft_printf("Error\nFailed to load images :(\n");
		exit_game(data, 1);
	}
	init_resizing(data);
}

static void	init_display(t_mlx_data *data)
/*
	This function initialize the window/display
*/
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width
			* data->cell_size, data->map_height * data->cell_size, "so_long");
	if (!data->win_ptr)
	{
		ft_printf("Error\nFailed to create a window\n");
		exit_game(data, 1);
	}
	init_image_loading(data);
}

static void	define_cell_size(t_mlx_data *data)
/*
	This function calculates cell_size if the map is bigger than the screen
*/
{
	data->cell_size = 64;
}

void	init_game(t_mlx_data *data)
/*
	This function initialize the game
*/
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
	define_cell_size(data);
	data->move_count = 0;
	data->score = 0;
	data->collectible_count = 0;
	data->exit_info.exit_visibility = 0;
	data->exit_info.win = 0;
	init_display(data);
	mlx_set_font(data->mlx_ptr, data->win_ptr,
		"-*-times-*-*-*-*-80-*-*-*-*-*-*-*");
}
