/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:24:43 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/04 22:01:45 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_image *img, int start_x, int start_y, int size)
{
	int	i;
	int	j;

	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			set_color_pixel(img, start_x + i, start_y + j);
	}
}

void	draw_minimap(t_cub *data)
{
	int		ms;
	int		x;
	int		y;

	ms = data->minimap_scale;
	y = -1;
	while (++y < data->cfg.map_height)
	{
		x = -1;
		while (++x < data->cfg.map_width)
		{
			if (data->cfg.map[y][x] == '1')
			{
				data->img.color = 0x888888;
				draw_square(&data->img, OFF_X + x * ms, OFF_Y + y * ms, ms);
			}
			else
			{
				data->img.color = 0x222222;
				draw_square(&data->img, OFF_X + x * ms, OFF_Y + y * ms, ms);
			}
		}
	}
	data->img.color = 0xFF0000;
	draw_square(&data->img, data->player.pos_x * ms + OFF_X - 2,
		data->player.pos_y * ms + OFF_Y - 2, 5);
}
