/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:59:01 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/02 20:15:50 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_cub *data)
{
	int	dx;

	(void)y;
	dx = x - data->last_mouse_x;
	if (dx > 0)
		turn(&data->player, ANGULAR_SPEED);
	else if (dx < 0)
		turn(&data->player, -ANGULAR_SPEED);
	data->last_mouse_x = x;
	return (0);
}

// int	resize_window(int new_w, int new_h, t_cub *data)
// {
// 	printf("Nouvelle taille : %d x %d\n", new_w, new_h);
// 	if (new_w <= 0 || new_h <= 0
// 		|| (new_w == data->img.width && new_h == data->img.height))
// 		return (0);
// 	mlx_destroy_image(data->mlx, data->img.ptr);
// 	data->img.width = new_w;
// 	data->img.height = new_h;
// 	data->img.ptr = mlx_new_image(data->mlx,
// 			data->img.width, data->img.height);
// 	if (!data->img.ptr)
// 		error("Failed to resize image", EXIT_FAILURE, data);
// 	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
// 			&data->img.line_length, &data->img.endian);
// 	return (0);
// }
