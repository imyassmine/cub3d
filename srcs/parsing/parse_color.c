#include "cub3d.h"

/* NOTES:
On veut transformer R(red), G(green), B(blue) en une seule valeur binaire.asm
Exple:
r = 220 -> 0xDC
g = 100 -> 0x64
b = 0 -> 0x00

Chaque composante : un nombre entre 0 et 255, sur 1 octet (8 bits).
Donc ici par exemple on veut que RED soit décalé de 16 bits (r << 16),
GREEN de 8 et BLUE ne bouge pas.

(r << 16) = 0xDC0000
(g << 8)  = 0x006400
(b)       = 0x000000

Résultat final :
0xDC6400 (format RRGGBB)
*/

int	parse_color(char *line, t_config *cfg)
{
	char	**rgb;
	int		color;
	int		r;
	int		g;
	int		b;

	// vérifier si la ligne commence par "F "(floor) ou "C " (ceiling)
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		// il faut découper après le préfixe, exple "220, 100, 0"
		rgb = ft_split(line + 2, ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			return (1); // si format invalide

		// convertir txt -> int
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);

		// fusionner en une seule valeur de format 0xRRGGBB
		color = (r << 16) | (g << 8) | b;
		if (ft_strncmp(line, "F ", 2) == 0)
			cfg->floor_color = color;
		else
			cfg->ceiling_color = color;

		free_tab(rgb);
		return (0);
	}
	return (1);
}
