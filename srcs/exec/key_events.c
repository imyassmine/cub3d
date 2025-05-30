/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:57:19 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/30 22:56:22 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_cub *data)
{
	if (keycode == ESC)
		clean_exit(0, data);
	else if (keycode == W || keycode == UP)
		data->player.forward = 1;
	else if (keycode == S || keycode == DOWN)
		data->player.backward = 1;
	else if (keycode == A)
		data->player.left = 1;
	else if (keycode == D)
		data->player.right = 1;
	else if (keycode == LEFT)
		data->player.turn_left = 1;
	else if (keycode == RIGHT)
		data->player.turn_right = 1;
	else if (keycode == C)
	{
		if (data->cursor_visible)
			mlx_mouse_hide(data->mlx, data->win);
		else
			mlx_mouse_show(data->mlx, data->win);
		data->cursor_visible = !data->cursor_visible;
	}
	return (0);
}

int	key_release(int keycode, t_cub *data)
{
	if (keycode == W || keycode == UP)
		data->player.forward = 0;
	else if (keycode == S || keycode == DOWN)
		data->player.backward = 0;
	else if (keycode == A)
		data->player.left = 0;
	else if (keycode == D)
		data->player.right = 0;
	else if (keycode == LEFT)
		data->player.turn_left = 0;
	else if (keycode == RIGHT)
		data->player.turn_right = 0;
	return (0);
}

int	close_window(t_cub *data)
{
	clean_exit(0, data);
	return (0);
}
