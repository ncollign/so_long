/*Map :
    - Map fermée par des murs
    - Map rectangle ou carrée
    - Si map incorrecte : renvoyer une erreur ("Error\n + Erreur")
    - 0 : emplacement vide
    - 1 : Mur
    - C : Item à collecter (min 1)
    - E : Sortie (min 1)
    - P : Position de départ du personnage (min 1)
    - Vérifier si chemin possible (Juste si des cases autour de la position de base ou chemin complet ?)
        Si chemin complet : Utiliser principe du démineur (fonction récursive)*/
#include "so_long.h"

/*void    checkWalls(void)
{
    
}*/

Tile    getMapSize(const char *map_path)
{
    Tile	size;
    int	map_fd;
    char	*line;

    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
		size.comment = "Error\nMap file could not be open.";
	else
	{
		line = get_next_line(map_fd);
		size.x = ft_strlen(line) - 2;
		size.y = 0;
		while (get_next_line(map_fd) != NULL)
			size.y++;
		size.y++;
		if (size.y < 4 || size.x < 4)
			size.comment = "Error\nThe map is too small";
		else
			size.comment = "OK";
	}
    close(map_fd);
    return (size);
}

int	checkMapPath(char *map_path)
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