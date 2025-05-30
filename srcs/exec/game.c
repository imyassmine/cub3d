/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:58:27 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/31 00:42:09 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor_ceiling(t_image *img, int ceiling_color, int floor_color)
{
	int	*line;
	int	color;
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		if (y < img->height / 2)
			color = ceiling_color;
		else
			color = floor_color;
		line = (int *)img->addr + y * (img->line_length / 4);
		x = -1;
		while (++x < img->width)
			line[x] = color;
	}
}

int	game_loop(t_cub *data)
{
	move_player(data, &data->player);
	draw_floor_ceiling(&data->img, data->cfg.ceiling_color,
		data->cfg.floor_color);
	render_walls(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img.ptr, 0, 0);
	return (0);
}
