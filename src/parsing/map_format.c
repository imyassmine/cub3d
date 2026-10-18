#include "cub3d.h"

int	has_empty_line_inside(char **map)
{
	int	i;
	int	found_empty;

	i = 0;
	found_empty = 0;
	while (map[i])
	{
		if (is_empty_line(map[i]))
			found_empty = 1;
		else if (found_empty)
		{
			printf("Error: ligne vide au milieu de la map\n");
			return (1);
		}
		i++;
	}
	return (0);
}
