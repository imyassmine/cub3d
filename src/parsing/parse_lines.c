#include "cub3d.h"

static int	assign_texture(char **tokens, t_config *cfg, char *resolved_path)
{
	if (ft_strcmp(tokens[0], "NO") == 0 && cfg->north_texture == NULL)
		cfg->north_texture = resolved_path;
	else if (ft_strcmp(tokens[0], "SO") == 0 && cfg->south_texture == NULL)
		cfg->south_texture = resolved_path;
	else if (ft_strcmp(tokens[0], "WE") == 0 && cfg->west_texture == NULL)
		cfg->west_texture = resolved_path;
	else if (ft_strcmp(tokens[0], "EA") == 0 && cfg->east_texture == NULL)
		cfg->east_texture = resolved_path;
	else if (ft_strcmp(tokens[0], "DO") == 0 && cfg->door_texture == NULL)
		cfg->door_texture = resolved_path;
	else
	{
		free(resolved_path);
		return (1);
	}
	return (0);
}

static int	store_texture_path(char **tokens, t_cub *data)
{
	char	*resolved_path;

	resolved_path = resolve_texture_path(tokens[1], &data->gc);
	if (!resolved_path)
		return (1);
	if (!validate_texture_file(resolved_path))
	{
		printf("Erreur: Fichier texture introuvable ou illisible: %s\n",
			tokens[1]);
		free(resolved_path);
		return (1);
	}
	return (assign_texture(tokens, &data->cfg, resolved_path));
}

int	parse_line(char *line, t_cub *data)
{
	char	**tokens;

	if (is_empty_line(line))
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (free_split(tokens), 1);
	if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
		return (free_split(tokens), parse_color(line, &data->cfg));
	if (store_texture_path(tokens, data))
		return (free_split(tokens), 1);
	return (free_split(tokens), 0);
}
