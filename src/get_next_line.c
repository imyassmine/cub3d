#include "cub3d.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[70000];
	int			i = 0;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			r = read(fd, buffer, BUFFER_SIZE);
			if (r <= 0)
				break ;
			buffer_read = r;
			buffer_pos = 0;
		}
		line[i++] = buffer[buffer_pos++];
		if (buffer[buffer_pos - 1] == '\n')
			break ;
	}
	if (i == 0)
		return (NULL);
	line[i] = '\0';
	return (ft_strdup(line));
}
