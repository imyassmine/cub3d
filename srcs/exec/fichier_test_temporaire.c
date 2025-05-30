#include "cub3d.h"

static void lst_to_map(t_cub *data, t_list *lst, int height, int width)
{
	data->cfg.map_height = height;
	data->cfg.map_width  = width;
	data->cfg.map = malloc(sizeof(char*) * height);
	if (!data->cfg.map)
		error("Malloc failed", EXIT_FAILURE, data);
	for (int i = 0; i < height; i++)
	{
		char *line = lst->content;
		int   len  = ft_strlen(line);
		char *buf  = malloc(width + 1);
		if (!buf)
			error("Malloc failed", EXIT_FAILURE, data);
		ft_memcpy(buf, line, len);
		ft_memset(buf + len, '0', width - len);
		buf[width] = '\0';
		data->cfg.map[i] = buf;
		for (int j = 0; buf[j]; j++)
			if (ft_strchr("NSEW", buf[j]))
			{
				data->cfg.player_start_x = j;
				data->cfg.player_start_y = i;
				data->cfg.player_dir     = buf[j];
				buf[j] = '0';
			}
		lst = lst->next;
	}
}

void fontion_temporaire(const char *filename, t_cub *data)
{
	int     fd = open(filename, O_RDONLY);
	t_list *lines = NULL;
	char   *line;
	int     height = 0;
	int     width  = 0;

	if (fd < 0)
		error("Cannot open map file", EXIT_FAILURE, data);
	while ((line = get_next_line(fd)))
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		height++;
		if ((int)ft_strlen(line) > width)
			width = ft_strlen(line);
	}
	close(fd);
	if (height == 0)
		error("Empty map file", EXIT_FAILURE, data);
	lst_to_map(data, lines, height, width);
	ft_lstclear(&lines, free);
}
