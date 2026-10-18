#include "cub3d.h"

static int	is_space_surrounded(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1])
		return (0);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (0);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (0);
	return (1);
}

// vérifie que chaque case '0' est bien entourée (càd pas de vide autour)
int	is_valid_open_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!is_space_surrounded(map, i, j))
					return (printf("Error: case ouverte (%d,%d)\n", i, j), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
