#define MAP_WIDTH 15
#define MAP_HEIGHT 5
#define MAP_PATH "../maps/map1.ber"
#include "../libft/libft.h"
#include "../libft/libft.a"
#include <fcntl.h>

// Structure représentant une case de la carte
typedef	struct
{
	int	isEmpty;
   char	type;
} Tile;

void	mapRead(Tile map[MAP_HEIGHT][MAP_WIDTH])
{
	char	*line;
	int	x;
	int	y;
	int	map_fd = open(MAP_PATH, O_RDONLY);

	if (map_fd == -1)
	{
		ft_printf("Erreur lors du chargement de la carte !");
	}
	// Ajouter sécurités pour ouverture de la carte

	line = ft_calloc(MAP_WIDTH, sizeof(int));
	line = get_next_line(map_fd);
	y = 0;
	while (y < MAP_HEIGHT && line != NULL)
	{
		x = 0;
		line = get_next_line(map_fd);
		while (x < MAP_WIDTH && line[x] != '\0')
		{
			map[y][x].type = line[x];
			x++;
		}
		ft_free(&line);
		y++;
	}
	close(map_fd);
}

// Printf la carte dans le terminal
void	printMap(const Tile map[MAP_HEIGHT][MAP_WIDTH])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			ft_printf("%c", map[y][x].type);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	main(void)
{
	Tile map[MAP_HEIGHT][MAP_WIDTH];

	// Lire la carte
	mapRead(map);
	printMap(map);

	return (0);
}