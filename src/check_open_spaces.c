#include "cub3d.h"

//vérifie que chaque case '0' est bien entourée (càd pas de vide autour)
int	is_valid_open_spaces(char **map)
{
	int	i = 0, j;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1] ||
					map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
					map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (printf("Error: case ouverte (%d,%d)\n", i, j), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

