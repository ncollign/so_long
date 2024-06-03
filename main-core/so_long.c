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

void initGame(t_mlx_data *data)
/* This function initialize the game */
{
	t_img *original_background;
    t_img *original_walls;
    t_img *original_collectibles;
    t_img *original_player;
    t_img *original_exit;

    if (!data)
	{
		ft_printf("Error\nData is not defined\n");
		exit_game(data, 1);
	}
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_printf("Error\nFailed to initialize MinilibX\n");
		exit_game(data, 1);
	}
	data->cell_size = 64;
	data->move_count = 0;
	data->score = 0;
	data->collectible_count = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * data->cell_size, data->map_height * data->cell_size, "So_Long");
	if (!data->win_ptr)
	{
		ft_printf("Error\nFailed to create a window\n");
		exit_game(data, 1);
	}
	original_background = load_image(data->mlx_ptr, "../ressources/background_texture.xpm");
	original_walls = load_image(data->mlx_ptr, "../ressources/wall_texture.xpm");
	original_collectibles = load_image(data->mlx_ptr, "../ressources/collectible_texture.xpm");
	original_player = load_image(data->mlx_ptr, "../ressources/player/player_texture.xpm");
	original_exit = load_image(data->mlx_ptr, "../ressources/exit_texture.xpm");
	data->background = resize_image(data->mlx_ptr, original_background, data->cell_size, data->cell_size);
	data->walls = resize_image(data->mlx_ptr, original_walls, data->cell_size, data->cell_size);
	data->collectibles = resize_image(data->mlx_ptr, original_collectibles, data->cell_size, data->cell_size);
	data->player = resize_image(data->mlx_ptr, original_player, data->cell_size, data->cell_size);
	data->exit = resize_image(data->mlx_ptr, original_exit, data->cell_size, data->cell_size);
	mlx_destroy_image(data->mlx_ptr, original_background->image);
	mlx_destroy_image(data->mlx_ptr, original_walls->image);
	mlx_destroy_image(data->mlx_ptr, original_collectibles->image);
	mlx_destroy_image(data->mlx_ptr, original_player->image);
	mlx_destroy_image(data->mlx_ptr, original_exit->image);
	free(original_background);
	free(original_walls);
    free(original_collectibles);
    free(original_player);
    free(original_exit);
}

int	main(int argc, char *argv[])
/* Main function */
{
	char	*map_path;
	t_mlx_data *data;

	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
    if (!data)
		return (EXIT_FAILURE);
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
	getMapSize(data, map_path);
	mapRead(data, map_path);
	initGame(data);
	checkMap(data);
	render_map(data);
	mlx_key_hook(data->win_ptr, (int (*)())handle_input, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}