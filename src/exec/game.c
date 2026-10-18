#include "cub3d.h"

int	game_loop(t_cub *data)
{
	move_player(data, &data->player);
	if (data->show_starry_sky == true)
	{
		update_starry_sky(data);
		draw_starry_sky(data);
		draw_floor_ceiling(&data->img, data->cfg.ceiling_color,
			data->cfg.floor_color, true);
	}
	else
		draw_floor_ceiling(&data->img, data->cfg.ceiling_color,
			data->cfg.floor_color, false);
	draw_walls(data);
	if (data->show_cursor == true)
		mlx_mouse_show(data->mlx, data->win);
	else
		mlx_mouse_hide(data->mlx, data->win);
	if (data->show_minimap == true)
		draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img.ptr, 0, 0);
	if (data->show_help_menu == true)
		draw_help_menu(data);
	return (0);
}
