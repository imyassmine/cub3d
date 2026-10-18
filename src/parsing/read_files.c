#include "cub3d.h"

#define MAX_FILE_LINES 2048

void	remove_carriage_return(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\r')
			line[i] = '\0';
		i++;
	}
}

// lire et afficher un fichier sur la sortie standard
void	read_file(const char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		exit(1);
	}
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		write(1, buffer, bytes);
	}
	if (bytes < 0)
	{
		perror("error");
		close(fd);
		exit(1);
	}
	close(fd);
}

static char	**allocate_lines_array(void)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (MAX_FILE_LINES + 1));
	if (!lines)
		return (NULL);
	return (lines);
}

static int	read_lines_loop(int fd, char **lines)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		remove_carriage_return(line);
		lines[i++] = line;
		if (i >= MAX_FILE_LINES)
		{
			printf("Erreur: fichier trop long\n");
			lines[i] = NULL;
			return (i);
		}
	}
	lines[i] = NULL;
	return (i);
}

char	**read_file_lines(const char *filename)
{
	int		fd;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur ouverture fichier");
		return (NULL);
	}
	lines = allocate_lines_array();
	if (!lines)
		return (close(fd), NULL);
	read_lines_loop(fd, lines);
	close(fd);
	return (lines);
}
