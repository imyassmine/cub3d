#include "cub3d.h"

int	has_tabs(char *line)
{
	int	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int	all_elements_present(t_config *cfg)
{
	return (
		cfg->north_texture && cfg->south_texture &&
		cfg->west_texture && cfg->east_texture &&
		cfg->floor_color != -1 && cfg->ceiling_color != -1
	);
}

// trouver l’index de la première ligne de la map
int	first_map_line(char **lines)
{
	int	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	parse_file(char **lines, t_config *cfg)
{
	int	i = 0;
	int	start;

	while (lines[i] && !all_elements_present(cfg))
	{
		if (has_tabs(lines[i]))
			return (error("tab character in file", 1), 1);
		if (is_empty_line(lines[i]))
			i++;
		else if (parse_line(lines[i], cfg) != 0)
			return (1);
		else
			i++;
	}
	start = first_map_line(lines);
	if (start == -1)
		return (error("no map found", 1), 1);
	if (parse_map(lines, start, cfg) != 0)
		return (error("map extraction failed", 1), 1);
	while (lines[++start])
	{
		if (!is_empty_line(lines[start]))
			return (error("unexpected content after map", 1), 1);
	}
	return (0);
}
