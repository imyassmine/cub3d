#include "cub3d.h"

static int	has_one_player(char **map)
{
	int	i; 
	int	j;
	int	player_count;

    i = 0;
    player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

int is_valid_map(t_config *cfg)
{
	if (!has_one_player(cfg->map))
	{
		printf("Error: la map doit contenir exactement 1 joueur\n");
		return (0);
	}
	if (!has_only_valid_chars(cfg->map))
		return (0);
	if (!is_map_closed(cfg))
		return (0);
	return (1);
}

static int is_full_wall_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int is_map_closed(t_config *cfg)
{
    int i;
    int len;
    char *line;

    i = 0;

    //1. vérifier le bord du haut
    if (!is_full_wall_line(cfg->map[0]))
    {
        printf("Error: ligne du haut non fermée\n");
        return (0);
    }

    //2. vérifier le bord du bas
    if (!is_full_wall_line(cfg->map[cfg->map_height -1]))
    {
        printf("Error: ligne du bad non fermée\n");
        return (0);
    }

    //3. vérifier côté gauche et côté droit
    while (cfg->map[i])
    {
        line = cfg->map[i];
        len = ft_strlen(line);
        if (line[0] != '1' || line[len - 1] != '1')
        {
			printf("Error: ligne %d non fermée (gauche ou droite)\n", i);
            return (0);
        }
        i++;
    }
    return (1);
}

int has_only_valid_chars(char **map)
{
	int i;
	int j;

    i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (c != '0' && c != '1' && c != ' ' &&
				c != 'N' && c != 'S' && c != 'E' && c != 'W')
			{
				printf("Error: caractère invalide '%c' ligne %d colonne %d\n", c, i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
