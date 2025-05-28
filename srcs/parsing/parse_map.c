#include "cub3d.h"

static int	init_map(char **lines, int start_index, t_config *cfg)
{
	int	height;
	int	i;

	height = 0;
    i = 0;
	while (lines[start_index + height])
		height++;
	cfg->map = malloc(sizeof(char *) * (height + 1));
	if (!cfg->map)
		exit_error("malloc map failed", 1);
	while (i < height)
	{
		cfg->map[i] = ft_strdup(lines[start_index + i]);
		if (!cfg->map[i])
			exit_error("dup map line failed", 1);
		i++;
	}
	cfg->map[i] = NULL;
	cfg->map_height = height;
	return (0);
}

int	parse_map(char **lines, int start_index, t_config *cfg)
{
	int	i;
	int	len;

    i = 0;
	if (init_map(lines, start_index, cfg) != 0)
		return (1);
	cfg->map_width = 0;
	while (cfg->map[i])
	{
		len = ft_strlen(cfg->map[i]);
		if (len > cfg->map_width)
			cfg->map_width = len;
		i++;
	}
	return (0);
}

