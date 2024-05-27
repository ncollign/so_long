#include "../minilibx_linux/mlx.h"
#include "../main-core/so_long.h"
#include <stdio.h>

#define	WIDTH	400
#define HEIGHT	400

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixels;
	int		endian;
	int		line_len;
}	t_img;

typedef struct	s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx_data;

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixels / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	color_screen(t_mlx_data *data, int color)
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			my_pixel_put(&data->img, x, y, color);
		}	
	}
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		printf("Closing the window...");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	else if (keysym == XK_r)
	{
		color_screen(data, 0xff0000);
	}
	else if (keysym == XK_g)
	{
		color_screen(data, 0xff00);
	}
	else if (keysym == XK_b)
	{
		color_screen(data, 0xff);
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	//mlx_xpm_file_to_image(); SE RENSEIGNER
	
	//printf("The %d key has been pressed\n\n.", keysym);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;

	// Create Pointer to initialise mlx
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	
	// Create Window
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My window");
	if (data.win_ptr == NULL)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}

	// Define the image
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixels, &data.img.line_len, &data.img.endian);


	mlx_key_hook(data.win_ptr, handle_input, &data);

	// Loop to let the window open
	mlx_loop(data.mlx_ptr);

    mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);

    return (0);
}
