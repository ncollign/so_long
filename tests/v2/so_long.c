#include "../../main-core/so_long.h"

int getMapSize(t_mlx_data *data, const char *map_path)
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
        return (-1);
    }

    line = get_next_line(map_fd);
    if (line == NULL)
    {
        ft_printf("Error\nMap file is empty or could not be read.\n");
        close(map_fd);
        return (-1);
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
        return (-1);
    }

    data->map_width = x;
    data->map_height = y;
    return (0);
}

int mapRead(t_mlx_data *data, const char *map_path)
/* This function reads the fd containing the map and creates a 2D table with the map */
{
    char *line;
    int x, y;
    int map_fd;

    map_fd = open(map_path, O_RDONLY);
    if (map_fd == -1)
    {
        ft_printf("Error\nMap file could not be opened.\n");
        return (-1);
    }

    data->map = (Tile **)malloc(data->map_height * sizeof(Tile *));
    if (!data->map)
    {
        ft_printf("Error\nMemory allocation failed!\n");
        close(map_fd);
        return (-1);
    }

    y = 0;
    while ((line = get_next_line(map_fd)) != NULL && y < data->map_height)
    {
        data->map[y] = (Tile *)malloc(data->map_width * sizeof(Tile));
        if (!data->map[y])
        {
            ft_printf("Error\nMemory allocation failed!\n");
            ft_free(&line);
            close(map_fd);
            return (-1);
        }

        x = 0;
        while (x < data->map_width && line[x] != '\0')
        {
            data->map[y][x].type = line[x];
            x++;
        }

        ft_free(&line);
        y++;
    }

    close(map_fd);
    return (0);
}

void printMap(t_mlx_data *data)
/* This function prints the map in the terminal using ft_printf */
{
    int x;
    int y;

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            ft_printf("%c", data->map[y][x].type);
            x++;
        }
        ft_printf("\n");
        y++;
    }
}

int main(int argc, char *argv[])
/* Main function */
{
    char *map_path;
    t_mlx_data *data;
    int cell_size = 64;
    int is_ok;

    if (argc > 1)
    {
        map_path = argv[1];
    }
    else
    {
        map_path = "../../maps/map_default.ber";
    }

    data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
    if (!data)
    {
        return (EXIT_FAILURE);
    }

    is_ok = getMapSize(data, map_path);
    ft_printf("%d, %d\n", data->map_width, data->map_height);

    if (is_ok != 0)
    {
        free(data);
        return (EXIT_FAILURE);
    }

    if (mapRead(data, map_path) != 0)
    {
        free(data);
        return (EXIT_FAILURE);
    }

    printMap(data);

    for (int i = 0; i < data->map_height; i++)
    {
        free(data->map[i]);
    }
    free(data->map);
    free(data);

    return (EXIT_SUCCESS);
}
