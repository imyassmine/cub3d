/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:35:42 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/01 19:55:11 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player, t_config *cfg)
{
	if (cfg->player_start_dir == 'N')
		player->dir_y = -1.0;
	else if (cfg->player_start_dir == 'S')
		player->dir_y = 1.0;
	else if (cfg->player_start_dir == 'E')
		player->dir_x = 1.0;
	else if (cfg->player_start_dir == 'W')
		player->dir_x = -1.0;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}

void	init_game(t_cub *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Failed to initialize MLX library", EXIT_FAILURE, NULL);
	data->img.width = DEFAULT_WIN_WIDTH;
	data->img.height = DEFAULT_WIN_HEIGHT;
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
	data->show_cursor = true;
	data->show_minimap = true;
	// Données du parser (ci-dessous valeurs temporaires)
	data->cfg.ceiling_color = 0x0000FF;
	data->cfg.floor_color = 0x8B4513;
	if (MINIMAP_WIDTH / data->cfg.map_width
		< MINIMAP_HEIGHT / data->cfg.map_height)
		data->minimap_scale = MINIMAP_WIDTH / data->cfg.map_width;
	else
		data->minimap_scale = MINIMAP_HEIGHT / data->cfg.map_height;
	init_player(&data->player, &data->cfg);
}
