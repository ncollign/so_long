#include "../minilibx_linux/mlx.h"
#include "so_long.h"

#define WIDTH 800
#define HEIGHT 800

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

void *mlx_connection;
void *mlx_window;
// Pointeurs vers les images
void *player_img;

// Fonction pour charger les images
void	load_images()
{
    int img_width;
	int	img_height;

    //background_img = mlx_xpm_file_to_image(mlx_connection, "background.xpm", &img_width, &img_height);
    //wall_img = mlx_xpm_file_to_image(mlx_connection, "wall.xpm", &img_width, &img_height);
    //collectible_img = mlx_xpm_file_to_image(mlx_connection, "collectible.xpm", &img_width, &img_height);
    player_img = mlx_xpm_file_to_image(mlx_connection, "../ressources/player/player.xpm", &img_width, &img_height);

    if (!player_img)
	{
        ft_printf("Error loading images\n");
        exit(1);
    }
}

// Fonction pour dessiner le joueur
void draw_player(int x, int y)
{
    mlx_put_image_to_window(mlx_connection, mlx_window, player_img, x, y);
}

int main(void) {
    /*mlx_connection = mlx_init();
    if (mlx_connection == NULL) {
        ft_printf("Failed to initialize MiniLibX\n");
        return 1;
    }

    mlx_window = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "Game Window");
    if (mlx_window == NULL) {
        ft_printf("Failed to create window\n");
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return 1;
    }

    // Charger les images
    load_images();

    // Rendu des différents éléments
    draw_player(0, 0);  // Position initiale du joueur

    // Démarrer la boucle d'événements
    mlx_loop(mlx_connection);

    // Nettoyage
    mlx_destroy_image(mlx_connection, player_img);
    mlx_destroy_window(mlx_connection, mlx_window);
    mlx_destroy_display(mlx_connection);
    free(mlx_connection);*/

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

    return 0;
}
