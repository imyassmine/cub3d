#include "cub3d.h"

int	print_help(void)
{
	ft_putendl_fd("Usage: ./cub3d [map.cub]", STDERR_FILENO);
	return (0);
}

void	clean_exit(int status, t_cub *data)
{
	if (data->win)
		(mlx_destroy_window(data->mlx, data->win));
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	gc_cleanup(&data->gc);
	printf("Thanks for playing!\n");
	exit(status);
}

void	error(const char *error_msg, int status, t_cub *data)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (status == 2)
		print_help();
	if (data)
		clean_exit(status, data);
	else
		exit(status);
}
