#include "cub3d.h"

// extraire la map à partir d’un tableau de lignes
//en commençant à l’indice `start`
// renvoyer un tableau alloué contenant uniquement les lignes de la map
char	**extract_map(char **lines, int start)
{
	int		i;
	int		count;
	char	**map;

	i = 0;
	count = 0;
	while (lines[start + count])
		count++;
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	while (i < count)
	{
		map[i] = ft_strdup(lines[start + i]);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	pad_map_lines(char **map, int width, t_gc *gc)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			newline = gc_malloc(width + 1, gc);
			if (!newline)
				exit_error("malloc pad map", 1);
			ft_memcpy(newline, map[i], len);
			while (len < width)
				newline[len++] = ' ';
			newline[width] = '\0';
			gc_free(map[i], gc);
			map[i] = newline;
		}
		i++;
	}
}

// Fonction pour vérifier si la carte contient des portes
int	map_has_doors(t_config *cfg)
{
	int	x;
	int	y;

	if (!cfg->map)
		return (0);
	y = -1;
	while (++y < cfg->map_height)
	{
		x = -1;
		while (++x < cfg->map_width && cfg->map[y])
		{
			if (cfg->map[y][x] == 'D')
				return (1);
		}
	}
	return (0);
}
