/*
    - Vérifier si chemin possible (Juste si des cases autour de la position de base ou chemin complet ?)
        Si chemin complet : Utiliser principe du démineur (fonction récursive)
*/
#include "so_long.h"

Tile	checkMap(Tile map_info, const Tile map[map_info.x][map_info.y])
/* This function checks if the map is OK and have all the specifications in the subject*/
{
    int	x;
	int	y;
	int	hasCollectible;
	int	hasPlayer;
	int hasExit;

	hasExit = 0;
	hasPlayer = 0;
	hasCollectible = 0;
	y = 0;
	while (y < map_info.y)
	{
		x = 0;
		while (x < map_info.x)
		{
			if ((x == 0) || (x == map_info.x - 1))
			{
				if (map[x][y].type != '1')
					map_info.comment = "Error\nThe map is not closed with walls or is not rectangular"; // Toutes les lignes doivent être de la même longueur pour être rectangulaire
			}
			if ((y == 0) || (y == map_info.y - 1))
			{
				if (map[x][y].type != '1')
					map_info.comment = "Error\nThe map is not closed with walls or is not rectangular";
			}
			if (map[x][y].type == 'C')
				hasCollectible++;
			if (map[x][y].type == 'P')
				hasPlayer++;
			if (map[x][y].type == 'E')
				hasExit++;
			x++;
		}
		y++;
	}
	if (hasCollectible == 0)
		map_info.comment = "Error\nThe map must have minimum 1 item to collect";
	if ((hasPlayer == 0) || (hasPlayer > 1))
		map_info.comment = "Error\nThe map must have 1 player";
	if ((hasExit == 0) || (hasExit > 1))
		map_info.comment = "Error\nThe map must have 1 exit";
	return (map_info);
}

int	getMapSize(t_mlx_data *data, const char *map_path)
/* This function gives the size of the map */
{
    //Tile	size;
    int	map_fd;
	int	x;
	int	y;
    char	*line;

	x = 0;
	y = 0;
    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
	{
		ft_printf("Error\nMap file could not be open.");
		return (-1);
	}
	else
	{
		line = get_next_line(map_fd);
		x = ft_strlen(line) - 2;
		y = 0;
		while (get_next_line(map_fd) != NULL)
			y++;
		y++;
		if (y < 4 || x < 4)
		{	
			ft_printf("Error\nThe map is too small");
			return (-1);
		}
	}
    close(map_fd);
	data->map_width = x;
	data->map_height = y;
    return (0);
}

int	checkMapPath(char *map_path)
/* This function verify that the fd is a .ber and if it exists */
{
	int	map_fd;

	if (ft_strnstr(map_path, ".ber", ft_strlen(map_path)))
	{
    	map_fd = open(map_path, O_RDONLY);
		if (map_fd == -1)
		{
			close(map_fd);
			return (0);
		}
		else
		{
			close(map_fd);
			return (1);
		}	
	}
	return (0);
}