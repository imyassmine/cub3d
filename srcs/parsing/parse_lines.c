#include "cub3d.h"

int	parse_line(char *line, t_config *cfg)
{
	int	type;

	// on identifie le type de la ligne
	type = get_line_type(line);
	if (type == 0)
		return (0); // ligne vide → on l'ignore
	else if (type == 1)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			cfg->north_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			cfg->south_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			cfg->west_texture = ft_strdup(line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			cfg->east_texture = ft_strdup(line + 3);
	}
	else if (type == 2)
	{
		// ligne de couleur (F ou C)
		if (parse_color(line, cfg) != 0)
			return (1);
	}
	else if (type == 3)
		return (1); // début de map → on arrête le parsing ici
	return (0);
}
