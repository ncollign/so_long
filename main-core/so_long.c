#include "so_long.h"

int	mapRead(const Tile map_info, Tile map[map_info.x][map_info.y], const char *map_path)
/* This function reads the fd containing the map and create a 2d table with the map*/
{
	char	*line;
	int	x;
	int	y;
	int	map_fd ;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		ft_printf("Error\nMap file could not be open.");
	line = ft_calloc(map_info.x + 1, sizeof(char));
	if (!line)
		ft_printf("Error\nMemory allocation failed !");
	y = 0;
	while (y < map_info.y && line != NULL)
	{
		x = 0;
		line = get_next_line(map_fd);
		while (x < map_info.x && line[x] != '\0')
		{
			map[x][y].type = line[x];
			map[x][y].x = x;
			map[x][y].y = y;
			x++;
		}
		y++;
	}
	ft_free(&line);
	close(map_fd);
	return (1);
}

void	printMap(const Tile map_info, const Tile map[map_info.x][map_info.y])
/* This function prints the map in the terminal using ft_printf */
{
	int	x;
	int	y;

	y = 0;
	while (y < map_info.y)
	{
		x = 0;
		while (x < map_info.x)
		{
			ft_printf("%c", map[x][y].type);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

t_mlx_data *initGame(int map_width, int map_height, int cell_size)
/* This function initialize the game */
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

int	main(int argc, char *argv[])
/* Main function */
{
	char	*map_path;
	Tile	map_info;
	
	int cell_size = 64;
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
	map_info = getMapSize(map_path);
	if (ft_strncmp(map_info.comment, "OK", 3) != 0)
		ft_printf("%s\n", map_info.comment);
	else
	{
		Tile map[map_info.x][map_info.y];
		mapRead(map_info, map, map_path);
		//printMap(map_info, map);
		map_info = checkMap(map_info, map);
		if (ft_strncmp(map_info.comment, "OK", 3) != 0)
			ft_printf("%s\n", map_info.comment);
		else
		{
			t_mlx_data *mlx_data = initGame(map_info.x, map_info.y, cell_size);
			if (!mlx_data)
			{
				ft_printf("Failed to initialize the game\n");
				return (EXIT_FAILURE);
			}
			render_map(mlx_data, map_info, map);
			mlx_key_hook(mlx_data->win_ptr, handle_input, &mlx_data);
			mlx_loop(mlx_data->mlx_ptr);
			free(mlx_data);
		}
	}
	return (EXIT_SUCCESS);
}