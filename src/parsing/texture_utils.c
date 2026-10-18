#include "cub3d.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

// Fonction pour résoudre un chemin de texture relatif
// Si le chemin commence par '/', il est déjà absolu
// Sinon, on le considère relatif au répertoire de travail actuel
char	*resolve_texture_path(const char *texture_path, t_gc *gc)
{
	char	*resolved_path;
	int		len;

	if (!texture_path)
		return (NULL);
	if (texture_path[0] == '/')
		resolved_path = ft_strdup_gc(texture_path, gc);
	else
		resolved_path = ft_strdup_gc(texture_path, gc);
	if (!resolved_path)
		return (NULL);
	len = strlen(resolved_path);
	while (len > 0 && (resolved_path[len - 1] == '\n' || resolved_path[len
				- 1] == '\r' || resolved_path[len - 1] == ' '
			|| resolved_path[len - 1] == '\t'))
	{
		resolved_path[len - 1] = '\0';
		len--;
	}
	return (resolved_path);
}

// Fonction pour vérifier si un fichier de texture existe et est lisible
int	validate_texture_file(const char *texture_path)
{
	int	fd;

	if (!texture_path)
		return (0);
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
