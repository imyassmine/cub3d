#include "cub3d.h"

int	init_player(t_config *cfg)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (cfg->map[i])
	{
		j = 0;
		while (cfg->map[i][j])
		{
			if (cfg->map[i][j] == 'N' || cfg->map[i][j] == 'S'
				|| cfg->map[i][j] == 'E' || cfg->map[i][j] == 'W')
			{
				if (count == 0)
				{
					cfg->player.x = j + 0.5;
					cfg->player.y = i + 0.5;
					cfg->player.direction = cfg->map[i][j];
					cfg->map[i][j] = '0';
				}
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		printf("Error: il doit y avoir exactement 1 joueur dans la map (trouvé: %d)\n", count);
		return (0);
	}
	return (1);
}
