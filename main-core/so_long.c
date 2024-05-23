#include "so_long.h"

int	mapRead(const Tile map_size, Tile map[map_size.x][map_size.y], const char *map_path)
/* This function reads the fd containing the map and create a 2d table with the map*/
{
	char	*line;
	int	x;
	int	y;
	int	map_fd ;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		ft_printf("Erreur lors du chargement de la carte !");
	// Ajouter sécurités pour ouverture de la carte
	line = ft_calloc(map_size.x + 1, sizeof(char));
	if (!line)
		ft_printf("Erreur lors du chargement de la carte !");
	y = 0;
	while (y < map_size.y && line != NULL)
	{
		x = 0;
		line = get_next_line(map_fd);
		while (x < map_size.x && line[x] != '\0')
		{
			map[x][y].type = line[x];
			x++;
		}
		y++;
	}
	ft_free(&line);
	close(map_fd);
	return (1);
}

void	printMap(const Tile map_size, const Tile map[map_size.x][map_size.y])
/* This function prints the map in the terminal using ft_printf */
{
	int	x;
	int	y;
	int	map_height;
	int	map_width;

	y = 0;
	while (y < map_size.y)
	{
		x = 0;
		while (x < map_size.x)
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
	Tile	map_size;

	map_size = getMapSize(map_path);
	if (ft_strncmp(map_size.comment, "OK", ft_strlen(map_size.comment)) == 1)
		ft_printf("%s\n", map_size.comment);
	else
	{
		Tile map[map_size.x][map_size.y];
		mapRead(map_size, map, map_path);
		printMap(map_size, map);
	}
}

int	main(int argc, char *argv[])
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