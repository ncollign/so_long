#include "so_long.h"

t_img	*load_image(void *mlx_ptr, char *path)
/* This function load an image into the memory */
{
	t_img *img = malloc(sizeof(t_img));
	if (!img)
		return NULL;
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
    if (!img->img_ptr)
    {
        free(img);
        return NULL;
    }
    img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
    return img;
}

t_img *create_image(void *mlx_ptr, int width, int height)
/* This function create the image */
{
    t_img *img = malloc(sizeof(t_img));
    if (!img)
        return NULL;
    img->img_ptr = mlx_new_image(mlx_ptr, width, height);
    if (!img->img_ptr)
    {
        free(img);
        return NULL;
    }
    img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
    img->width = width;
    img->height = height;
    return img;
}

t_img *resize_image(void *mlx_ptr, t_img *src_img, int new_width, int new_height)
/* This function resize the image display the right size on the window */
{
    t_img *new_img = create_image(mlx_ptr, new_width, new_height);
    if (!new_img)
        return NULL;

    double x_ratio = (double)src_img->width / new_width;
    double y_ratio = (double)src_img->height / new_height;

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int src_x = (int)(x * x_ratio);
            int src_y = (int)(y * y_ratio);
			int color = *(int *)(src_img->data + (src_y * src_img->size_line + src_x * (src_img->bpp / 8)));
			*(int *)(new_img->data + (y * new_img->size_line + x * (new_img->bpp / 8))) = color;
        }
    }
    return new_img;
}

void refresh_cell(t_mlx_data *mlx_data, int x, int y)
/* This function refresh a cell on the display */
{
    if (mlx_data->map[y][x].type == '1')
        mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->walls->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
    else if (mlx_data->map[y][x].type == 'C')
        mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->collectibles->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
    else if (mlx_data->map[y][x].type == 'P')
        mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->player->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
    else if (mlx_data->map[y][x].type == 'E')
        mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->exit->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
    else
        mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->background->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
}

// Function to render the map
void	render_map(t_mlx_data *data)
{
    for (int y = 0; y < data->map_height; y++)
    {
        for (int x = 0; x < data->map_width; x++)
        {
            if (data->map[y][x].type == '1') // Wall
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->walls->img_ptr, x * data->cell_size, y * data->cell_size);
            else if (data->map[y][x].type == 'C') // Collectible
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collectibles->img_ptr, x * data->cell_size, y * data->cell_size);
            else if (data->map[y][x].type == 'P') // Player
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player->img_ptr, x * data->cell_size, y * data->cell_size);
            else if (data->map[y][x].type == 'E') // Exit
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit->img_ptr, x * data->cell_size, y * data->cell_size);
            else // Background
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background->img_ptr, x * data->cell_size, y * data->cell_size);
        }
    }
}

void	exit_game(t_mlx_data *data)
{
	int		i;
	
	ft_printf("Closing the window...");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	

    // Libérez la carte si elle a été allouée dynamiquement
	i = 0;
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
    free(data);
}