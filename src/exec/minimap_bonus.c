#include "cub3d.h"

static int	get_cell_color(t_cub *data, int x, int y)
{
	t_door	*door;

	if (data->cfg.map[y][x] == '1')
		return (GREY);
	if (data->cfg.map[y][x] == 'D')
	{
		door = find_door_at(data, x, y);
		if (door && door->state == DOOR_CLOSED)
			return (ORANGE);
		else
			return (GREEN);
	}
	return (DARK_GREY);
}

void	draw_minimap(t_cub *data)
{
	int	ms;
	int	x;
	int	y;

	ms = data->minimap_scale;
	y = -1;
	while (++y < data->cfg.map_height)
	{
		x = -1;
		while (++x < data->cfg.map_width)
		{
			data->img.color = get_cell_color(data, x, y);
			draw_square(&data->img, OFF_X + x * ms, OFF_Y + y * ms, ms);
		}
	}
	data->img.color = BLUE;
	draw_square(&data->img, data->player.pos_x * ms + OFF_X - 2,
		data->player.pos_y * ms + OFF_Y - 2, 5);
}
