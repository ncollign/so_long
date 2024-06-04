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

void	init_display(t_mlx_data *data)
{
	t_img *original_background;
    t_img *original_walls;
    t_img *original_collectibles;
    t_img *original_player1;
	t_img *original_player2;
    t_img *original_exit;
	t_img *original_enemy;

	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * data->cell_size, data->map_height * data->cell_size, "So_Long");
	if (!data->win_ptr)
	{
		ft_printf("Error\nFailed to create a window\n");
		exit_game(data, 1);
	}
	original_background = load_image(data->mlx_ptr, "../ressources/background_texture.xpm");
	original_walls = load_image(data->mlx_ptr, "../ressources/wall_texture.xpm");
	original_collectibles = load_image(data->mlx_ptr, "../ressources/collectible_texture.xpm");
	original_player1 = load_image(data->mlx_ptr, "../ressources/player/player_texture1.xpm");
	original_player2 = load_image(data->mlx_ptr, "../ressources/player/player_texture2.xpm");
	original_exit = load_image(data->mlx_ptr, "../ressources/exit_texture.xpm");
	original_enemy = load_image(data->mlx_ptr, "../ressources/enemy_texture.xpm");
	if (original_background == NULL || original_walls == NULL || original_collectibles == NULL || original_player1 == NULL || original_player2 == NULL || original_exit == NULL || original_enemy == NULL)
		exit_game(data, 1);
	data->background = resize_image(data->mlx_ptr, original_background, data->cell_size, data->cell_size);
	data->walls = resize_image(data->mlx_ptr, original_walls, data->cell_size, data->cell_size);
	data->collectibles = resize_image(data->mlx_ptr, original_collectibles, data->cell_size, data->cell_size);
	data->player1 = resize_image(data->mlx_ptr, original_player1, data->cell_size, data->cell_size);
	data->player2 = resize_image(data->mlx_ptr, original_player2, data->cell_size, data->cell_size);
	data->exit = resize_image(data->mlx_ptr, original_exit, data->cell_size, data->cell_size);
	data->enemy = resize_image(data->mlx_ptr, original_enemy, data->cell_size, data->cell_size);
	mlx_destroy_image(data->mlx_ptr, original_background->image);
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
}