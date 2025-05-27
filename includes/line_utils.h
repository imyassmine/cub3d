#ifndef LINE_UTILS_H
# define LINE_UTILS_H

int	is_empty_line(char *line);
int is_texture_line(char *line);
int is_color_line(char *line);
int is_map_line(char *line);
int get_line_type(char *line);


#endif
