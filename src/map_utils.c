#include "cub3d.h"

// extraire la map à partir d’un tableau de lignes, en commençant à l’indice `start`
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
			// en cas d’erreur d’alloc, on free ce qui a été déjà copié
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
