/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:35:28 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/31 00:41:59 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	cast_ray(t_cub *data, int x)
{
	t_player	*p = &data->player;
	double		camera_x = 2 * x / (double)data->img.width - 1;
	double		ray_dir_x = p->dir_x + p->plane_x * camera_x;
	double		ray_dir_y = p->dir_y + p->plane_y * camera_x;
	int			map_x = (int)p->pos_x;
	int			map_y = (int)p->pos_y;
	double		delta_dist_x = fabs(1.0 / ray_dir_x);
	double		delta_dist_y = fabs(1.0 / ray_dir_y);
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit = 0;
	int			side;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (p->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - p->pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (p->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - p->pos_y) * delta_dist_y;
	}
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (data->cfg.map[map_y][map_x] != '0')
			hit = 1;
	}
	double perp_dist = (side == 0)
		? (map_x - p->pos_x + (1 - step_x) / 2.0) / ray_dir_x
		: (map_y - p->pos_y + (1 - step_y) / 2.0) / ray_dir_y;
	int line_h = (int)(data->img.height / perp_dist);
	int draw_start = data->img.height / 2 - line_h / 2;
	int draw_end   = data->img.height / 2 + line_h / 2;
	if (draw_start < 0) draw_start = 0;
	if (draw_end >= data->img.height) draw_end = data->img.height - 1;
	int color = (side == 0) ? 0xFFFFFF : 0x7F7F7F;
	int *pixels = (int *)data->img.addr;
	int pitch  = data->img.line_length / 4;
	for (int y = draw_start; y <= draw_end; y++)
		pixels[y * pitch + x] = color;
}

void	render_walls(t_cub *data)
{
	int	x;

	x = -1;
	while (++x < data->img.width)
		cast_ray(data, x);
}
