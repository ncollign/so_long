#define MAP_WIDTH 15
#define MAP_HEIGHT 5
#define MAP_PATH "../maps/map1.ber"
#include "../libft/libft.a"
#include <fcntl.h>

// Structure représentant une case de la carte
typedef	struct
{
    char	type;
} Tile;

/*void	map_read(Tile (*map)[MAP_WIDTH][MAP_HEIGHT]) // A vérifier lors de la compilation
{
	char	*line;
	int	x;
	int	y;
	int	map_fd = open(MAP_PATH, O_RDONLY);
	
	if (map_fd == -1)
	{
		ft_printf("Erreur lors du chargement de la carte !");
	}
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		line = get_next_line(map_fd);
		while (x < MAP_WIDTH)
		{
			map->map[x][y].type = line[x];
			x++;
		}
		ft_free(&line);
		y++;
	}
}

int	main(void)
{
	Tile map[MAP_WIDTH][MAP_HEIGHT];

	// Lire la carte
	map_read(map);
	// Tester si map est bien modifiée

	return (0);
}*/

Tile** map_read(void)
{
    Tile **map = malloc(MAP_HEIGHT * sizeof(Tile*)); // Allouer un tableau 2D

    if (map == NULL)
    {
        ft_printf("Erreur lors de l'allocation de la mémoire pour la carte");
		return (NULL);
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        map[y] = malloc(MAP_WIDTH * sizeof(Tile)); // Allouer un tableau de lignes

        if (map[y] == NULL)
        {
            ft_printf("Erreur lors de l'allocation de la mémoire pour une ligne de la carte");
			return (NULL);
		}
    }

    int map_fd = open(MAP_PATH, O_RDONLY);
    if (map_fd == -1)
    {
        ft_printf("Erreur lors de l'ouverture du fichier de la carte");
		return (NULL);
    }

    char *line;
    int y = 0;
    while ((line = get_next_line(map_fd)) != NULL && y < MAP_HEIGHT)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            map[y][x].type = line[x];
        }
        free(line);
        y++;
    }

    close(map_fd);
    return map;
}

int main(void)
{
    Tile **map = map_read();

    // Tester si map est bien récupérée
    // Par exemple, afficher le type de chaque case de la carte
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            ft_printf("%c ", map[y][x].type);
        }
        ft_printf("\n");
    }

    // Libérer la mémoire allouée pour le tableau 2D
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
    }
    free(map);

    return 0;
}
