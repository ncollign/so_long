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

static void	free_images(t_mlx_data *data)
{
	if (data->background != NULL)
		mlx_destroy_image(data->mlx_ptr, data->background->image);
	if (data->walls != NULL)
		mlx_destroy_image(data->mlx_ptr, data->walls->image);
	if (data->collectibles != NULL)
		mlx_destroy_image(data->mlx_ptr, data->collectibles->image);
	if (data->player1 != NULL)
		mlx_destroy_image(data->mlx_ptr, data->player1->image);
	if (data->player2 != NULL)
		mlx_destroy_image(data->mlx_ptr, data->player2->image);
	if (data->exit != NULL)
		mlx_destroy_image(data->mlx_ptr, data->exit->image);
	if (data->enemy != NULL)
		mlx_destroy_image(data->mlx_ptr, data->enemy->image);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

void	exit_game(t_mlx_data *data, int error_catch)
{
	int		y;

	ft_printf("Closing the window...\n");
	if (data->map != NULL)
	{
		y = 0;
		while (y < data->map_height)
		{
			free(data->map[y]);
			y++;
		}
		free(data->map);
	}
	free_images(data);
	exit (error_catch);
}

t_img	*load_image(void *mlx_ptr, char *path)
/*
	This function loads an image into the memory
*/
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->image = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->width, &img->height);
	if (!img->image)
	{
		free(img);
		return (NULL);
	}
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->size_line, &img->format);
	return (img);
}

t_img	*create_image(void *mlx_ptr, int width, int height)
/*
	This function creates an image
*/
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->image = mlx_new_image(mlx_ptr, width, height);
	if (!img->image)
	{
		free(img);
		return (NULL);
	}
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->size_line, &img->format);
	img->width = width;
	img->height = height;
	return (img);
}

/*static void	destroy_original_images(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->image);
	mlx_destroy_image(data->mlx_ptr, original_walls->image);
	mlx_destroy_image(data->mlx_ptr, original_collectibles->image);
	mlx_destroy_image(data->mlx_ptr, original_player1->image);
	mlx_destroy_image(data->mlx_ptr, original_player2->image);
	mlx_destroy_image(data->mlx_ptr, original_exit->image);
	mlx_destroy_image(data->mlx_ptr, original_enemy->image);
	free(original_background);
	free(original_walls);
	free(original_collectibles);
	free(original_player1);
	free(original_player2);
	free(original_exit);
	free(original_enemy);
}*/

/*static void	resize_images(t_mlx_data *data)
{

}*/

static void	load_images(t_mlx_data *data)
{
	data->background = load_image(data->mlx_ptr,
			"../ressources/background_texture.xpm");
	data->walls = load_image(data->mlx_ptr,
			"../ressources/wall_texture.xpm");
	data->collectibles = load_image(data->mlx_ptr,
			"../ressources/collectible_texture.xpm");
	data->player1 = load_image(data->mlx_ptr,
			"../ressources/player/player_texture1.xpm");
	data->player2 = load_image(data->mlx_ptr,
			"../ressources/player/player_texture2.xpm");
	data->exit = load_image(data->mlx_ptr,
			"../ressources/exit_texture.xpm");
	data->enemy = load_image(data->mlx_ptr,
			"../ressources/enemy_texture.xpm");
	if ((data->background == NULL) || (data->walls == NULL)
		|| (data->collectibles == NULL) || (data->player1 == NULL)
		|| (data->player2 == NULL) || (data->exit == NULL)
		|| (data->enemy == NULL))
		exit_game(data, 1);
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

void	init_display(t_mlx_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * data->cell_size, data->map_height * data->cell_size, "So_Long");
	if (!data->win_ptr)
	{
		ft_printf("Error\nFailed to create a window\n");
		exit_game(data, 1);
	}
	load_images(data);
	//destroy_original_images(data);
}