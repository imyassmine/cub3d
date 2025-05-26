/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:57:19 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/26 22:30:28 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_cub *data)
{
	if (keycode == ESC)
		clean_exit(0, data);
/* 	else if (keycode == SHIFT)
		data->color.shift += 1;
	else if (keycode == PLUS)
		data->f.iteration_max += SCALE_ITERATION;
	else if (keycode == R)
		reset_view(&data->f, &data->img);
	else if (keycode == W || keycode == UP)
		data->f.view.center_y += (MOVE_STEP / data->f.view.scale);
	else if (keycode == S || keycode == DOWN)
		data->f.view.center_y -= (MOVE_STEP / data->f.view.scale);
	else if (keycode == A || keycode == LEFT)
		data->f.view.center_x -= (MOVE_STEP / data->f.view.scale);
	else if (keycode == D || keycode == RIGHT)
		data->f.view.center_x += (MOVE_STEP / data->f.view.scale);
	render(data); */
	return (0);
}

/* int	key_release(int keycode, t_cub *data)
{
	if (keycode == SPACE)
		data->space_key = 0;
	return (0);
} */

int	close_window(t_cub *data)
{
	clean_exit(0, data);
	return (0);
}
