#include "cub3d.h"

int	has_tabs(char *line)
{
	int	i;

	i = 0;
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
	int	basic_elements_present;

	basic_elements_present = (cfg->north_texture && cfg->south_texture
			&& cfg->west_texture && cfg->east_texture && cfg->floor_color != -1
			&& cfg->ceiling_color != -1);
	if (map_has_doors(cfg))
		return (basic_elements_present && cfg->door_texture);
	return (basic_elements_present);
}

// trouver l’index de la première ligne de la map
int	first_map_line(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	check_after_map(char **lines, int start)
{
	while (lines[++start])
	{
		if (!is_empty_line(lines[start]))
			return (error("unexpected content after map", 1, NULL), 1);
	}
	return (0);
}

int	parse_file(char **lines, t_cub *data)
{
	int	start;

	if (parse_until_map(lines, data) != 0)
		return (1);
	start = first_map_line(lines);
	if (start == -1)
		return (error("no map found", 1, NULL), 1);
	if (parse_map(lines, start, data) != 0)
		return (error("map extraction failed", 1, NULL), 1);
	if (check_after_map(lines, start) != 0)
		return (1);
	return (0);
}
