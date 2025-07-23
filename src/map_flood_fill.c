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


// fonction récursive qui remplit depuis la case (x, y)
// retourne 0 si on touche l'extérieur, sinon 1
static int flood(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || y >= height || x >= (int)ft_strlen(map[y]))
		return (0); // on sort de la map
	if (map[y][x] == ' ')
		return (0); // on touche une case vide
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1); // mur ou déjà visité

	map[y][x] = 'X'; // marquer comme visité

	if (!flood(map, x + 1, y, width, height))
		return (0);
	if (!flood(map, x - 1, y, width, height))
		return (0);
	if (!flood(map, x, y + 1, width, height))
		return (0);
	if (!flood(map, x, y - 1, width, height))
		return (0);

	return (1);
}

int is_map_closed(t_config *cfg)
{
	char	**map_copy;
	int		res;

	map_copy = duplicate_map(cfg->map);
	if (!map_copy)
		return (printf("Erreur: malloc map copy\n"), 0);
	res = flood(
		map_copy,
		(int)cfg->player.x,
		(int)cfg->player.y,
		cfg->map_width,
		cfg->map_height
	);
	free_tab(map_copy);
	if (!res)
	{
		printf("Erreur: map non fermée (flood)\n");
		return (0);
	}
	return (1);
}
