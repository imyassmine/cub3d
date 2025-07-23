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

void	free_split(char **tab)
{
	int	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])     
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (s1[i] - s2[i]); 
}


void	error(const char *error_msg, int status)
{
	int	len;

	len = 0;
	while (error_msg[len])
		len++;
	write(2, "Error\n", 6);
	write(2, error_msg, len);
	write(2, "\n", 1);
	exit(status);
}


