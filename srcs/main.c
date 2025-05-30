#include "cub3d.h"

/*
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
*/

int	main(int argc, char **argv)
{
	t_cub	data;

	if (argc != 2)
		error("Invalid number of arguments.", 2, NULL);
	if (argc == 2 && !ft_strncmp(argv[1], "--help", 6) && !argv[1][6])
		return (print_help());
	ft_memset(&data, 0, sizeof(t_cub));
	// Ici, fonctions parsing
	fontion_temporaire(argv[1], &data);
	init_game(&data);
	mlx_hook(data.win, KEY_PRESS, KEYPRESSMASK, key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, KEYRELEASEMASK, key_release, &data);
	mlx_hook(data.win, MOTION_NOTIFY, POINTERMOTIONMASK, mouse_move, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, STRUCNOTIFYMASK, close_window, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
