/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:35:42 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/26 22:29:04 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_cub *data)
{
	ft_memset(data, 0, sizeof(t_cub));
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Failed to initialize MLX library", EXIT_FAILURE, NULL);
	data->img.width = 1500;
	data->img.height = 800;
	data->win = mlx_new_window(data->mlx,
			data->img.width, data->img.height, "Cub3D");
	if (!data->win)
		error("Failed to create window", EXIT_FAILURE, data);
	data->img.ptr = mlx_new_image(data->mlx,
			data->img.width, data->img.height);
	if (!data->img.ptr)
		error("Failed to create image", EXIT_FAILURE, data);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
}
