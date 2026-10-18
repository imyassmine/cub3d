#include "cub3d.h"

// Ligne totalement vide ou ne contenant que des espaces/tabs ou \n
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Texture : NO/SO/WE/EA/DO, éventuellement précédé d'espaces/tabs
int	is_texture_line(char *line)
{
	int	i;

	i = skip_spaces(line);
	if (ft_strncmp(&line[i], "NO ", 3) == 0 || ft_strncmp(&line[i], "SO ",
			3) == 0 || ft_strncmp(&line[i], "WE ", 3) == 0
		|| ft_strncmp(&line[i], "EA ", 3) == 0 || ft_strncmp(&line[i], "DO ",
			3) == 0)
		return (1);
	return (0);
}

// Couleurs : F/C, éventuellement précédé d'espaces/tabs
int	is_color_line(char *line)
{
	int	i;

	i = skip_spaces(line);
	if (ft_strncmp(&line[i], "F ", 2) == 0 || ft_strncmp(&line[i], "C ",
			2) == 0)
		return (1);
	return (0);
}

// Ligne de map : au moins un caractère map valide
int	is_map_line(char *line)
{
	int	i;

	i = skip_spaces(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != 'D'
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

// Get le type de la ligne
int	get_line_type(char *line)
{
	if (is_empty_line(line))
		return (0);
	if (is_texture_line(line))
		return (1);
	if (is_color_line(line))
		return (2);
	if (is_map_line(line))
		return (3);
	return (-1);
}
