#include "cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0); 
		i++;
	}
	return (1); 
}

int is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (1); 
	return (0); 
}

int is_color_line(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1); 
	return (0); 
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\0') // sécurité ajoutée
		return (0);
	while (line[i])
    {
        printf("caractère[%d] = '%c' (%d)\n", i, line[i], (unsigned char)line[i]); //debug
        if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\n' && line[i] != '\r')
			return (0);
        i++;
    }
	return (1);
}

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

