#include "../minilibx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_img
{
    void        *img_ptr;
    char        *data;
    int         width;
    int         height;
    int         bpp;
    int         size_line;
    int         endian;
}               t_img;

typedef struct  s_mlx_data
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_img       *background;
    t_img       *walls;
    t_img       *collectibles;
    t_img       *player;
    t_img       *exit;
    int         map_width;
    int         map_height;
    int         cell_size;
}               t_mlx_data;

// Function to load an image
t_img *load_image(void *mlx_ptr, char *path)
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

// Function to create a new image
t_img *create_image(void *mlx_ptr, int width, int height)
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

// Function to get pixel color from an image
int get_pixel_color(t_img *img, int x, int y)
{
    int color = *(int *)(img->data + (y * img->size_line + x * (img->bpp / 8)));
    return color;
}

// Function to set pixel color in an image
void set_pixel_color(t_img *img, int x, int y, int color)
{
    *(int *)(img->data + (y * img->size_line + x * (img->bpp / 8))) = color;
}

// Function to resize an image
t_img *resize_image(void *mlx_ptr, t_img *src_img, int new_width, int new_height)
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
            int color = get_pixel_color(src_img, src_x, src_y);
            set_pixel_color(new_img, x, y, color);
        }
    }
    return new_img;
}

// Function to initialize the game data
t_mlx_data *init_game(int map_width, int map_height, int cell_size)
{
    t_mlx_data *mlx_data = malloc(sizeof(t_mlx_data));
    if (!mlx_data)
        return NULL;
    
    mlx_data->mlx_ptr = mlx_init();
    if (!mlx_data->mlx_ptr)
    {
        free(mlx_data);
        return NULL;
    }
    
    mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, map_width * cell_size, map_height * cell_size, "Game Window");
    if (!mlx_data->win_ptr)
    {
        free(mlx_data->mlx_ptr);
        free(mlx_data);
        return NULL;
    }

    // Load original images
    t_img *original_background = load_image(mlx_data->mlx_ptr, "../ressources/background_texture.xpm");
    t_img *original_walls = load_image(mlx_data->mlx_ptr, "../ressources/wall_texture.xpm");
    t_img *original_collectibles = load_image(mlx_data->mlx_ptr, "../ressources/collectible_texture.xpm");
    t_img *original_player = load_image(mlx_data->mlx_ptr, "../ressources/player/player_texture.xpm");
    t_img *original_exit = load_image(mlx_data->mlx_ptr, "../ressources/exit_texture.xpm");
    
    // Resize images
    mlx_data->background = resize_image(mlx_data->mlx_ptr, original_background, cell_size, cell_size);
    mlx_data->walls = resize_image(mlx_data->mlx_ptr, original_walls, cell_size, cell_size);
    mlx_data->collectibles = resize_image(mlx_data->mlx_ptr, original_collectibles, cell_size, cell_size);
    mlx_data->player = resize_image(mlx_data->mlx_ptr, original_player, cell_size, cell_size);
    mlx_data->exit = resize_image(mlx_data->mlx_ptr, original_exit, cell_size, cell_size);
    
    // Free original images
    mlx_destroy_image(mlx_data->mlx_ptr, original_background->img_ptr);
    mlx_destroy_image(mlx_data->mlx_ptr, original_walls->img_ptr);
    mlx_destroy_image(mlx_data->mlx_ptr, original_collectibles->img_ptr);
    mlx_destroy_image(mlx_data->mlx_ptr, original_player->img_ptr);
    mlx_destroy_image(mlx_data->mlx_ptr, original_exit->img_ptr);
    free(original_background);
    free(original_walls);
    free(original_collectibles);
    free(original_player);
    free(original_exit);
    
    mlx_data->map_width = map_width;
    mlx_data->map_height = map_height;
    mlx_data->cell_size = cell_size;
    
    return mlx_data;
}

// Function to render the map
void render_map(t_mlx_data *mlx_data, char **map)
{
    for (int y = 0; y < mlx_data->map_height; y++)
    {
        for (int x = 0; x < mlx_data->map_width; x++)
        {
            if (map[y][x] == '1') // Wall
                mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->walls->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
            else if (map[y][x] == 'C') // Collectible
                mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->collectibles->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
            else if (map[y][x] == 'P') // Player
                mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->player->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
            else if (map[y][x] == 'E') // Exit
                mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->exit->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
            else // Background
                mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->background->img_ptr, x * mlx_data->cell_size, y * mlx_data->cell_size);
        }
    }
}

int main()
{
    // Define a simple map
    char *map[] = {
        "111111",
        "1P0C01",
        "100001",
        "1C0E01",
        "111111"
    };

    // Define cell size (e.g., 64x64 pixels)
    int cell_size = 64;

    // Initialize the game
    t_mlx_data *mlx_data = init_game(6, 5, cell_size);
    if (!mlx_data)
    {
        fprintf(stderr, "Failed to initialize the game\n");
        return EXIT_FAILURE;
    }

    // Render the map
    render_map(mlx_data, map);

    // Enter the main loop
    mlx_loop(mlx_data->mlx_ptr);

    // Free resources (normally you would also free images and window)
    free(mlx_data);

    return EXIT_SUCCESS;
}
