#include "cub3d.h"

static int	store_texture_path(char **tokens, t_config *cfg)
{
	if (ft_strcmp(tokens[0], "NO") == 0 && cfg->north_texture == NULL)
		cfg->north_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0 && cfg->south_texture == NULL)
		cfg->south_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0 && cfg->west_texture == NULL)
		cfg->west_texture = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0 && cfg->east_texture == NULL)
		cfg->east_texture = ft_strdup(tokens[1]);
	else
		return (1);
	return (0);
}

int	parse_line(char *line, t_config *cfg)
{
	char	**tokens;

	if (is_empty_line(line))
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (free_split(tokens), 1);
	if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
		return (free_split(tokens), parse_color(line, cfg));
	if (store_texture_path(tokens, cfg))
		return (free_split(tokens), 1);
	return (free_split(tokens), 0);
}
