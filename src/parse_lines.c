#include "cub3d.h"

int	parse_line(char *line, t_config *cfg)
{
	char	**tokens;

	if (is_empty_line(line))
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_split(tokens);
		return (1); // ligne invalide
	}
	if (ft_strcmp(tokens[0], "NO") == 0)
		cfg->north_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		cfg->south_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		cfg->west_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		cfg->east_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
	{
		free_split(tokens);
		return (parse_color(line, cfg)); // on parse à partir de la ligne brute
	}
	else
	{
		free_split(tokens);
		return (1); // ligne non reconnue
	}
	free_split(tokens);
	return (0);
}
