#include "cub3d.h"

int	key_press(int keycode, t_cub *data)
{
	if (keycode == ESC)
		clean_exit(0, data);
	else if (keycode == W || keycode == UP)
		data->player.forward = true;
	else if (keycode == S || keycode == DOWN)
		data->player.backward = true;
	else if (keycode == A)
		data->player.left = true;
	else if (keycode == D)
		data->player.right = true;
	else if (keycode == E)
		interact_with_door(data);
	else if (keycode == LEFT)
		data->player.turn_left = true;
	else if (keycode == RIGHT)
		data->player.turn_right = true;
	else if (keycode == C)
		data->show_cursor = !data->show_cursor;
	else if (keycode == M)
		data->show_minimap = !data->show_minimap;
	else if (keycode == N)
		data->show_starry_sky = !data->show_starry_sky;
	else if (keycode == H)
		data->show_help_menu = !data->show_help_menu;
	return (0);
}

int	key_release(int keycode, t_cub *data)
{
	if (keycode == W || keycode == UP)
		data->player.forward = false;
	else if (keycode == S || keycode == DOWN)
		data->player.backward = false;
	else if (keycode == A)
		data->player.left = false;
	else if (keycode == D)
		data->player.right = false;
	else if (keycode == LEFT)
		data->player.turn_left = false;
	else if (keycode == RIGHT)
		data->player.turn_right = false;
	return (0);
}

int	close_window(t_cub *data)
{
	clean_exit(0, data);
	return (0);
}
