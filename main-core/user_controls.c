#include "so_long.h"

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_printf("Closing the window...");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	else if (keysym == XK_Up)
	{
		ft_printf("HAUT\n");
	}
	else if (keysym == XK_Down)
	{
		ft_printf("BAS\n");
	}
	else if (keysym == XK_Left)
	{
		ft_printf("GAUCHE\n");
	}
	else if (keysym == XK_Right)
	{
		ft_printf("DROITE\n");
	}

	return (0);
}

void	player_move(void)
{

}