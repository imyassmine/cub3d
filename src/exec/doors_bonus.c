#include "cub3d.h"

void	init_doors(t_cub *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = -1;
	while (++y < data->cfg.map_height)
	{
		x = -1;
		while (++x < data->cfg.map_width)
			if (data->cfg.map[y][x] == 'D')
				data->cfg.door_nb++;
	}
	if (data->cfg.door_nb == 0)
		return ;
	data->cfg.doors = gc_malloc(sizeof(t_door) * data->cfg.door_nb, &data->gc);
	y = -1;
	while (++y < data->cfg.map_height)
	{
		x = -1;
		while (++x < data->cfg.map_width)
			if (data->cfg.map[y][x] == 'D')
				data->cfg.doors[i++] = (t_door){x, y, DOOR_CLOSED};
	}
}

t_door	*find_door_at(t_cub *data, int x, int y)
{
	int	i;

	i = -1;
	while (++i < data->cfg.door_nb)
	{
		if (data->cfg.doors[i].x == x && data->cfg.doors[i].y == y)
			return (&data->cfg.doors[i]);
	}
	return (NULL);
}

int	is_door_closed(t_cub *data, int x, int y)
{
	t_door	*door;

	door = find_door_at(data, x, y);
	if (!door)
		return (1);
	return (door->state == DOOR_CLOSED);
}

/*
Le joueur peut interagir avec une porte a 1.5 cases de distance.
*/

void	interact_with_door(t_cub *data)
{
	int		door_x;
	int		door_y;
	t_door	*door;

	door_x = (int)(data->player.pos_x + data->player.dir_x * 1.5);
	door_y = (int)(data->player.pos_y + data->player.dir_y * 1.5);
	if (door_x >= 0 && door_x < data->cfg.map_width
		&& door_y >= 0 && door_y < data->cfg.map_height)
	{
		door = find_door_at(data, door_x, door_y);
		if (door)
		{
			if (door->state == DOOR_CLOSED)
				door->state = DOOR_OPEN;
			else if (door->state == DOOR_OPEN)
				door->state = DOOR_CLOSED;
		}
	}
}
