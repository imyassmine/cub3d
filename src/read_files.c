#include "cub3d.h"

#define MAX_FILE_LINES 2048

// en fait celle-ci sera sûrement à enlever, elle était utile pour supprimer 
// le '\r' qui vient de fichiers créés sous Windows (mon pc perso)
void	remove_carriage_return(char *line)
{
	int	i = 0;

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
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
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

char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur ouverture fichier");
		return (NULL);
	}
	lines = malloc(sizeof(char *) * (MAX_FILE_LINES + 1));
	if (!lines)
		return (close(fd), NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		remove_carriage_return(line);
		lines[i++] = line;
		if (i >= MAX_FILE_LINES)
		{
			printf("Erreur: fichier trop long\n");
			lines[i] = NULL;
			close(fd);
			return (lines);
		}
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
