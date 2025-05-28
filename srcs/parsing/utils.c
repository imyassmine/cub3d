#include "cub3d.h"

void	*exit_error(const char *msg, int code)
{
	perror(msg);
	exit(code);
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;
    
    i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
