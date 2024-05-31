#include "so_long.h"

int mapRead(t_mlx_data *data, const char *map_path)
/* This function reads the fd containing the map and creates a 2D table with the map */
{
    char *line;
    int x, y;
    int map_fd;

    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
    {
        ft_printf("Error\nMap file could not be opened.\n");
        return (-1);
    }

    data->map = (Tile **)malloc(data->map_height * sizeof(Tile *));
    if (!data->map)
    {
        ft_printf("Error\nMemory allocation failed!\n");
        close(map_fd);
        return (-1);
    }

    y = 0;
    while ((line = get_next_line(map_fd)) != NULL && y < data->map_height)
    {
        data->map[y] = (Tile *)malloc(data->map_width * sizeof(Tile));
        if (!data->map[y])
        {
            ft_printf("Error\nMemory allocation failed!\n");
            ft_free(&line);
            close(map_fd);
            return (-1);
        }

        x = 0;
        while (x < data->map_width && line[x] != '\0')
        {
            data->map[y][x].type = line[x];
            x++;
        }

        ft_free(&line);
        y++;
    }
    close(map_fd);
    return (0);
}

int initGame(t_mlx_data *data)
/* This function initialize the game */
{
    if (!data)
        return (1);
    
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        free(data);
        return (1);
    }
    
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * data->cell_size, data->map_height * data->cell_size, "So Long");
    if (!data->win_ptr)
    {
        free(data->mlx_ptr);
        free(data);
        return (1);
    }

    // Load original images
    t_img *original_background = load_image(data->mlx_ptr, "../ressources/background_texture.xpm");
    t_img *original_walls = load_image(data->mlx_ptr, "../ressources/wall_texture.xpm");
    t_img *original_collectibles = load_image(data->mlx_ptr, "../ressources/collectible_texture.xpm");
    t_img *original_player = load_image(data->mlx_ptr, "../ressources/player/player_texture.xpm");
    t_img *original_exit = load_image(data->mlx_ptr, "../ressources/exit_texture.xpm");
    
    // Resize images
    data->background = resize_image(data->mlx_ptr, original_background, data->cell_size, data->cell_size);
    data->walls = resize_image(data->mlx_ptr, original_walls, data->cell_size, data->cell_size);
    data->collectibles = resize_image(data->mlx_ptr, original_collectibles, data->cell_size, data->cell_size);
    data->player = resize_image(data->mlx_ptr, original_player, data->cell_size, data->cell_size);
    data->exit = resize_image(data->mlx_ptr, original_exit, data->cell_size, data->cell_size);
    
    // Free original images
    mlx_destroy_image(data->mlx_ptr, original_background->img_ptr);
    mlx_destroy_image(data->mlx_ptr, original_walls->img_ptr);
    mlx_destroy_image(data->mlx_ptr, original_collectibles->img_ptr);
    mlx_destroy_image(data->mlx_ptr, original_player->img_ptr);
    mlx_destroy_image(data->mlx_ptr, original_exit->img_ptr);
    free(original_background);
    free(original_walls);
    free(original_collectibles);
    free(original_player);
    free(original_exit);
    
    return (0);
}

int	main(int argc, char *argv[])
/* Main function */
{
	char	*map_path;
	t_mlx_data *data;
	int	error_catch;

	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
    if (!data)
        return (EXIT_FAILURE);
	
	data->cell_size = 64;
	if (argc < 2)
	{
		map_path = "../maps/map_default.ber";
		ft_printf("No map path given. Default settings applied.\n");
	}
	else
	{
		if (checkMapPath(argv[1]))
			{
				map_path = argv[1];
				ft_printf("Map path saved.\n");
			}
		else
		{
			map_path = "../maps/map_default.ber";
			ft_printf("Map path doesn't exist. Default settings applied.\n");
		}
	}
	error_catch = getMapSize(data, map_path);
	if (error_catch != 0)
		return (EXIT_FAILURE);
	else
	{
		mapRead(data, map_path);
		error_catch = checkMap(data);
		if (error_catch == 1)
			return (EXIT_FAILURE);
		else
		{
			error_catch = initGame(data);
			if (error_catch != 0)
			{
				ft_printf("Error\nFailed to initialize the game\n");
				return (EXIT_FAILURE);
			}
			render_map(data);
			mlx_key_hook(data->win_ptr, (int (*)())handle_input, data);
			mlx_loop(data->mlx_ptr);
			free(data);
		}
	}
	return (EXIT_SUCCESS);
}