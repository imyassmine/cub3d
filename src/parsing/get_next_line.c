#include "cub3d.h"

static int	read_buffer(int fd, char *buffer, int *buffer_pos, int *buffer_read)
{
	int	r;

	if (*buffer_pos >= *buffer_read)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			return (0);
		*buffer_read = r;
		*buffer_pos = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[70000];
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (!read_buffer(fd, buffer, &buffer_pos, &buffer_read))
			break ;
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos - 1] == '\n')
			break ;
	}
	if (i == 0)
		return (NULL);
	line[i] = '\0';
	return (ft_strdup(line));
}
