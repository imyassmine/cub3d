#include "cub3d.h"

int	check_file_valid(const char *filename)
{
	int			fd;
	struct stat	s;

	if (!filename || ft_strlen(filename) < 5)
	{
		printf("Error: fichier invalide\n");
		return (0);
	}
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
	{
		printf("Error: extension invalide (attendu .cub)\n");
		return (0);
	}
	if (stat(filename, &s) == 0 && S_ISDIR(s.st_mode))
	{
		printf("Error: le fichier est un dossier\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	return (close(fd), 1);
}

// pour refuser les lignes apres la map
int	check_lines_after_map(char **lines, int last_map_line)
{
	int	i;

	i = last_map_line + 1;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			printf("Error: unexpected line after map\n");
			return (1);
		}
		i++;
	}
	return (0);
}
