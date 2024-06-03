/*
    - Vérifier si chemin possible (Juste si des cases autour de la position de base ou chemin complet ?)
        Si chemin complet : Utiliser principe du démineur (fonction récursive)
*/
#include "so_long.h"

void	checkMap(t_mlx_data *data)
/*
This function checks if the map is OK and have all the specifications in the subject
Returns 0 if OK
Returns 1 if NOK
*/
{
    int	x;
	int	y;
	int	hasPlayer;
	int hasExit;

	hasExit = 0;
	hasPlayer = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((x == 0) || (x == data->map_width - 1))
			{
				if (data->map[y][x].type != '1')
				{
					// Toutes les lignes doivent être de la même longueur pour être rectangulaire
					ft_printf("Error\nThe map is not closed with walls or is not rectangular");
					exit_game(data, 1);
				}	 
			}
			if ((y == 0) || (y == data->map_height - 1))
			{
				if (data->map[y][x].type != '1')
				{
					ft_printf("Error\nThe map is not closed with walls or is not rectangular\n");
					exit_game(data, 1);
				}
			}
			if (data->map[y][x].type == 'C')
				data->collectible_count++;
			if (data->map[y][x].type == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				hasPlayer++;
			}
			if (data->map[y][x].type == 'E')
				hasExit++;
			x++;
		}
		y++;
	}
	if (data->collectible_count == 0)
	{
		ft_printf("Error\nThe map must have minimum 1 item to collect\n");
		exit_game(data, 1);
	}
	if ((hasPlayer == 0) || (hasPlayer > 1))
	{
		ft_printf("Error\nThe map must have 1 player\n");
		exit_game(data, 1);
	}
	if ((hasExit == 0) || (hasExit > 1))
	{
		ft_printf("Error\nThe map must have 1 exit\n");
		exit_game(data, 1);
	}
}

void	getMapSize(t_mlx_data *data, const char *map_path)
/* This function gives the size of the map */
{
    int map_fd;
    int x;
    int y;
    char *line;

    x = 0;
    y = 0;
    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
    {
        ft_printf("Error\nMap file could not be opened.\n");
        exit_game(data, 1);
    }

    line = get_next_line(map_fd);
    if (line == NULL)
    {
        ft_printf("Error\nMap file is empty or could not be read.\n");
        close(map_fd);
        exit_game(data, 1);
    }
    x = ft_strlen(line) - 2;
    ft_free(&line);
    y = 1;
    while ((line = get_next_line(map_fd)) != NULL)
    {
        ft_free(&line);
        y++;
    }
    close(map_fd);
    if (y < 4 || x < 4)
    {
        ft_printf("Error\nThe map is too small.\n");
        exit_game(data, 1);
    }
    data->map_width = x;
    data->map_height = y;
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