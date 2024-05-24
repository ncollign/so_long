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

void	initGame(char *map_path)
/* This function initialize the Game*/
{
	Tile	map_info;

	map_info = getMapSize(map_path);
	if (ft_strncmp(map_info.comment, "OK", 3) != 0)
		ft_printf("%s\n", map_info.comment);
	else
	{
		Tile map[map_info.x][map_info.y];
		mapRead(map_info, map, map_path);
		printMap(map_info, map);
		map_info = checkMap(map_info, map);
		if (ft_strncmp(map_info.comment, "OK", 3) != 0)
			ft_printf("%s\n", map_info.comment);
		else
		{
			// Si tout est OK

		}
	}
}

int	main(int argc, char *argv[])
/* Main function */
{
	char	*map_path;
	
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
	initGame(map_path);
	return (0);
}