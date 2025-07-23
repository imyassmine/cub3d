#ifndef UTILS_H
# define UTILS_H

char	*get_next_line(int fd);
void	*exit_error(const char *msg, int code);
void	free_tab(char **tab);
void	free_split(char **tab);
int ft_strcmp(char *s1, char *s2);
void	error(const char *error_msg, int status);


#endif
