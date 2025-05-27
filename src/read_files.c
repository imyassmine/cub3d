#include "cub3d.h"

void read_file(const char *filename)
{
    int fd;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes;

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

int	count_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("open failed", 1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**load_lines(const char *filename, int count)
{
	int		fd;
	char	**lines;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("re-open failed", 1);
	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		exit_error("malloc failed", 1);
	i = 0;
	while (i < count)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

char	**read_file_lines(char *filename)
{
	int		count;

	count = count_lines(filename);
	return (load_lines(filename, count));
}
