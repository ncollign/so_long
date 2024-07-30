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
/*
	This function free all the images on the display
	Also destroy the display
*/
{
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
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
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

void	exit_game(t_mlx_data *data, int error_catch)
/*
	This function exits the game properly
*/
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
