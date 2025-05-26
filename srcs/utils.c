/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 05:22:40 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/26 22:31:44 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_help(void)
{
	ft_putendl_fd("Usage: ./cub3d [map.cub]", STDERR_FILENO);
	ft_putendl_fd("Options:", STDERR_FILENO);
	ft_putendl_fd("  --help\t\tDisplay this help message", STDERR_FILENO);
	ft_putendl_fd("  --save\t\tSave the current game state", STDERR_FILENO);
	ft_putendl_fd("  --no-color\t\tDisable colored output", STDERR_FILENO);
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
	printf("Thanks for playing!\n");
	exit(status);
}

void	error(const char *error_msg, int status, t_cub *game)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (status == 2)
		print_help();
	if (game)
		clean_exit(status, game);
	else
		exit(status);
}
