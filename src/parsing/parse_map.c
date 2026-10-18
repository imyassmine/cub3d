#include "cub3d.h"

static int	init_map(char **lines, int start_index, t_cub *data)
{
	int	height;
	int	i;

	height = 0;
	i = 0;
	while (lines[start_index + height])
		height++;
	data->cfg.map = gc_malloc(sizeof(char *) * (height + 1), &data->gc);
	if (!data->cfg.map)
		exit_error("malloc map failed", 1);
	while (i < height)
	{
		data->cfg.map[i] = ft_strdup_gc(lines[start_index + i], &data->gc);
		if (!data->cfg.map[i])
			exit_error("dup map line failed", 1);
		i++;
	}
	data->cfg.map[i] = NULL;
	data->cfg.map_height = height;
	return (0);
}

int	parse_map(char **lines, int start_index, t_cub *data)
{
	int	i;
	int	len;

	i = 0;
	if (init_map(lines, start_index, data) != 0)
		return (1);
	data->cfg.map_width = 0;
	while (data->cfg.map[i])
	{
		len = ft_strlen(data->cfg.map[i]);
		if (len > data->cfg.map_width)
			data->cfg.map_width = len;
		i++;
	}
	pad_map_lines(data->cfg.map, data->cfg.map_width, &data->gc);
	return (0);
}
