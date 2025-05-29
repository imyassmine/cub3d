/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:35:42 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/29 19:36:34 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  game_loop(t_cub *data)
{
	move_player(data, &data->player);

	// // 2) Dessiner plafond / sol
	// draw_floor_ceiling(&data->img, data->cfg.ceiling_color,
	//                            data->cfg.floor_color);

	// // 3) Lancer le raycasting et dessiner les murs dans data->img
	// render_walls(data);
	mlx_put_image_to_window(data->mlx, data->win,
							data->img.ptr, 0, 0);
	return (0);
}

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
	game_loop(data);
	mlx_hook(data->win, KEY_PRESS, KEYPRESSMASK, key_press, &data);
	mlx_hook(data->win, KEY_RELEASE, KEYRELEASEMASK, key_release, &data);
	mlx_hook(data->win, DESTROY_NOTIFY, STRUCNOTIFYMASK, close_window, &data);
	mlx_loop(data->mlx);
}
