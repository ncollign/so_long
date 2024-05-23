#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
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

#endif

