#include "cub3d.h"

static char	**duplicate_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

static int	flood(char **map, int x, int y, int width)
{
	int	height;

	height = get_map_height(map);
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'D')
		return (1);
	map[y][x] = 'X';
	if (!flood(map, x + 1, y, width))
		return (0);
	if (!flood(map, x - 1, y, width))
		return (0);
	if (!flood(map, x, y + 1, width))
		return (0);
	if (!flood(map, x, y - 1, width))
		return (0);
	return (1);
}

int	is_map_closed(t_config *cfg)
{
	char	**map_copy;
	int		res;

	map_copy = duplicate_map(cfg->map);
	if (!map_copy)
		return (printf("Erreur: malloc map copy\n"), 0);
	res = flood(map_copy, (int)cfg->player.x, (int)cfg->player.y,
			cfg->map_width);
	free_tab(map_copy);
	if (!res)
	{
		printf("Erreur: map non fermée (flood)\n");
		return (0);
	}
	return (1);
}
