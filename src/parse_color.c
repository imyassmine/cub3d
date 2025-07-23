#include "cub3d.h"

static int	validate_and_convert_rgb(char **rgb, int *r, int *g, int *b)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (1);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (1);
	return (0);
}

int	parse_color(char *line, t_config *cfg)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	if (ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
		return (1);
	rgb = ft_split(line + 2, ',');
	if (validate_and_convert_rgb(rgb, &r, &g, &b))
		return (free_tab(rgb), 1);
	color = (r << 16) | (g << 8) | b;
	if (ft_strncmp(line, "F ", 2) == 0)
		cfg->floor_color = color;
	else
		cfg->ceiling_color = color;
	return (free_tab(rgb), 0);
}
