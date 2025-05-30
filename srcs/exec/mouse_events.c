/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:59:01 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/30 23:07:49 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_cub *data)
{
	int	dx;

	(void)y;
	dx = x - data->last_mouse_x;
	if (dx > 0)
		turn_right(&data->player);
	else if (dx < 0)
		turn_left(&data->player);
	data->last_mouse_x = x;
	return (0);
}
