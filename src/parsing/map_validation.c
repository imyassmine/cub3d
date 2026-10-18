#include "cub3d.h"

// Vérifie qu’il y a exactement 1 joueur (N/S/E/W) dans la map
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
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

int	is_valid_map(t_config *cfg)
{
	if (!has_one_player(cfg->map))
		return (printf("Error: Aucun joueur ou plusieurs joueurs trouvés\n"), 0);
	if (has_empty_line_inside(cfg->map))
		return (0);
	if (!has_only_valid_chars(cfg->map))
		return (0);
	if (!is_valid_open_spaces(cfg->map))
		return (0);
	if (!is_map_closed(cfg))
		return (0);
	return (1);
}

static int	is_valid_char(char c)
{
	if (c == '\n' || c == '\r')
		return (1);
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D')
		return (1);
	return (0);
}

static int	check_line_chars(char *line, int line_index)
{
	int		j;
	char	c;

	j = 0;
	while (line[j])
	{
		c = line[j];
		if (c == '\n' || c == '\r')
		{
			j++;
			continue ;
		}
		if (!is_valid_char(c))
		{
			printf("Error: caractère invalide '%c' ligne %d colonne %d\n",
				c, line_index, j);
			return (0);
		}
		j++;
	}
	return (1);
}

int	has_only_valid_chars(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!check_line_chars(map[i], i))
			return (0);
		i++;
	}
	return (1);
}
