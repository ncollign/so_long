#include "so_long.h"

void	exit_game(t_mlx_data *data, int	error_catch)
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
	if (data->background != NULL)
		mlx_destroy_image(data->mlx_ptr, data->background->image);
	if (data->walls != NULL)
		mlx_destroy_image(data->mlx_ptr, data->walls->image);
	if (data->collectibles != NULL)
		mlx_destroy_image(data->mlx_ptr, data->collectibles->image);
	if (data->player != NULL)
		mlx_destroy_image(data->mlx_ptr, data->player->image);
	if (data->exit != NULL)
		mlx_destroy_image(data->mlx_ptr, data->exit->image);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit (error_catch);
}

t_img	*load_image(void *mlx_ptr, char *path)
/*
	This function loads an image into the memory
*/
{
    t_img *img = malloc(sizeof(t_img));
    if (!img)
        return (NULL);
    img->image = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
    if (!img->image)
    {
        free(img);
        return (NULL);
    }
    img->data = mlx_get_data_addr(img->image, &img->bpp, &img->size_line, &img->format);
    return (img);
}

t_img *create_image(void *mlx_ptr, int width, int height)
/*
	This function creates an image
*/
{
    t_img *img = malloc(sizeof(t_img));
    if (!img)
        return (NULL);
    img->image = mlx_new_image(mlx_ptr, width, height);
    if (!img->image)
    {
        free(img);
		return (NULL);
    }
    img->data = mlx_get_data_addr(img->image, &img->bpp, &img->size_line, &img->format);
    img->width = width;
    img->height = height;
    return img;
}