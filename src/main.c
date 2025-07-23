#include "cub3d.h"

int	main(void)
{
	t_config	cfg;
	char		**lines;
	int			i;
	int			start;

	i = 0;
	start = 0;

	// initialiser toute la structure cfg à 0 (très important)
	ft_memset(&cfg, 0, sizeof(t_config));

	// lire toutes les lignes du fichier .cub
	lines = read_file_lines("map.cub");
	if (!lines)
		return (printf("Erreur: échec lecture fichier\n"), 1);

	// parcourir chaque ligne jusqu'à trouver le début de la map
	while (lines[i])
	{
		int type = get_line_type(lines[i]);

		if (type == 0)
			i++;
		else if (type == 1)
			parse_line(lines[i++], &cfg);
		else if (type == 2)
			parse_color(lines[i++], &cfg);
		else if (type == 3)
		{
			start = i;
			break ;
		}
		else if (type == -1)
		{
			printf("Erreur: ligne inconnue ou invalide\n");
			return (1);
		}
	}

	// étape numero uno: parser la map à partir de l'indice "start"
	if (parse_map(lines, start, &cfg) != 0)
		return (printf("Erreur: map invalide\n"), 1);

	// numero duo: trouver la position du joueur
	if (!init_player(&cfg))
		return (1);

	// numero tre: vérifier qu’il n’y a pas de ligne non vide après la map
	i = start + cfg.map_height;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			printf("Erreur: ligne non vide après la map\n");
			return (1);
		}
		i++;
	}

	// quareo: valider la map complète
	if (!is_valid_map(&cfg))
		return (1);

	// debug final: affichage des éléments extraits
	printf("North: %s\n", cfg.north_texture);
	printf("South: %s\n", cfg.south_texture);
	printf("West:  %s\n", cfg.west_texture);
	printf("East:  %s\n", cfg.east_texture);
	printf("Floor color:   0x%06X\n", cfg.floor_color);
	printf("Ceiling color: 0x%06X\n", cfg.ceiling_color);
	printf("Map size: %d x %d\n", cfg.map_width, cfg.map_height);
	printf("Joueur: x=%.1f y=%.1f angle=%c\n", cfg.player.x, cfg.player.y, cfg.player.direction);

	free_config(&cfg);
	free_tab(lines);
	return (0);
}
