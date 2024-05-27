#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

typedef	struct
{
	char	*comment;
	char	type;
	int	x;
	int	y;
} Tile;

Tile    getMapSize(const char *map_path);
int	checkMapPath(char *map_path);
Tile	checkMap(Tile map_info, const Tile map[map_info.x][map_info.y]);

#endif

