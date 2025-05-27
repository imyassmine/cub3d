#include "cub3d.h"

int	main(void)
{
	t_config	cfg;
	char		**lines;
	int			i;
	int			start;

	i = 0;
	start = 0;
	
	// initialise cfg à 0 (important pour éviter les valeurs aléatoires)
	ft_memset(&cfg, 0, sizeof(t_config));

	// lire le fichier map.cub
	lines = read_file_lines("map.cub");

	// analyser chaque ligne jusqu'à trouver le début de la map
	while (lines[i])
	{
		int type = get_line_type(lines[i]);

		// debug temporaire : afficher le type de chaque ligne
		printf("ligne %d: type %d\n", i, type);

		if (parse_line(lines[i], &cfg) == 1) // ligne inconnue = début de map
		{
			start = i;
			break ;
		}
		i++;
	}

	// ici on ajoute le parsing de la map
	parse_map(lines, start, &cfg);

	// valider la map (joueur, fermeture, etc)
	if (!is_valid_map(&cfg))
	{
		printf("Map invalide.\n");
		return (1);
	}

	// afficher ce qui a été lu
	printf("North:  %s\n", cfg.north_texture);
	printf("South:  %s\n", cfg.south_texture);
	printf("West:   %s\n", cfg.west_texture);
	printf("East:   %s\n", cfg.east_texture);

	printf("Floor:  0x%06X\n", cfg.floor_color);
	printf("Ceil:   0x%06X\n", cfg.ceiling_color);

	printf("Map height: %d\n", cfg.map_height);
	printf("Map width:  %d\n", cfg.map_width);

	// plus tard : free les lignes et textures
	return (0);
}
