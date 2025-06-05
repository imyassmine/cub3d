/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:58:27 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/05 05:14:38 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color_pixel(t_image *img, int x, int y)
{
	int	pixel;

	pixel = (y * img->line_length) + (x * img->bpp / 8);
	 *(unsigned int *)(img->addr + pixel) = img->color;
}

static void	draw_floor_ceiling(t_image *img, int ceiling_color, int floor_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		if (y < img->height / 2)
			img->color = ceiling_color;
		else
			img->color = floor_color;
		x = -1;
		while (++x < img->width)
			set_color_pixel(img, x, y);
	}
}

int	game_loop(t_cub *data)
{
	move_player(data, &data->player);
	draw_floor_ceiling(&data->img, data->cfg.ceiling_color,
		data->cfg.floor_color);
	render_walls(data);
	if (data->show_cursor == false)
		mlx_mouse_hide(data->mlx, data->win);
	else
		mlx_mouse_show(data->mlx, data->win);
	if (data->show_minimap == true)
		draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img.ptr, 0, 0);
	return (0);
}
