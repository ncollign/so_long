#define MAP_WIDTH 15
#define MAP_HEIGHT 5
#define MAP_PATH "../maps/map1.ber"

// Structure représentant une case de la carte
typedef	struct
{
    char	type;
} Tile;

void	map_read(Tile *map[MAP_WIDTH][MAP_HEIGHT]) // A vérifier lors de la compilation
{
	char	*line;
	int	x;
	int	y;
	int	map_fd = open(MAP_PATH, O_RDONLY);
	
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
		y++;
	}
}

int	main(void)
{
	Tile map[MAP_WIDTH][MAP_HEIGHT];

	// Lire la carte
	map_read(&map);
	// Tester si map est bien modifiée

	return (0);
}

