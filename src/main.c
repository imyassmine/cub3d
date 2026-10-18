#include "cub3d.h"

// Parsing et validation du fichier .cub : pas de debug ici
int	parse_and_validate(char *filename, t_cub *data)
{
	char	**lines;
	int		start;
	int		ret;

	lines = read_file_lines(filename);
	if (!lines)
		return (error("Erreur lecture fichier", 1, NULL), 1);
	start = parse_until_map(lines, data);
	if (start == -1)
	{
		free_tab(lines);
		free_config(&data->cfg);
		return (1);
	}
	if (!all_elements_present(&data->cfg))
	{
		free_tab(lines);
		free_config(&data->cfg);
		return (error("Éléments manquants (textures/couleurs)", 1, NULL), 1);
	}
	ret = parse_map(lines, start, data);
	free_tab(lines);
	return (ret);
}

// Parsing des lignes avant la map (textures/couleurs)
int	parse_until_map(char **lines, t_cub *data)
{
	int	type;
	int	i;

	if (!lines || !lines[0])
		return (error("Fichier vide", 1, NULL), -1);
	i = 0;
	while (lines[i])
	{
		type = get_line_type(lines[i]);
		if (type == 0)
			;
		else if (type == 1 && parse_line(lines[i], data) != 0)
			return (error("Erreur parsing texture", 1, NULL), -1);
		else if (type == 2 && parse_color(lines[i], &data->cfg) != 0)
			return (error("Erreur parsing couleur", 1, NULL), -1);
		else if (type == 3)
			return (i);
		else if (type != 1 && type != 2)
			return (error("Ligne invalide dans le fichier", 1, NULL), -1);
		i++;
	}
	return (error("Aucune map trouvée", 1, NULL), -1);
}

int	main(int argc, char **argv)
{
	t_cub	data;

	if (argc != 2)
		return (error("Invalid number of arguments.", 2, NULL), 1);
	if (!check_file_valid(argv[1]))
		return (error("Fichier .cub invalide ou illisible.", 1, NULL), 1);
	ft_memset(&data, 0, sizeof(t_cub));
	if (parse_and_validate(argv[1], &data) != 0)
		return (free_config(&data.cfg), 1);
	if (!is_valid_map(&data.cfg))
		return (free_config(&data.cfg), 1);
	if (!init_player(&data.cfg))
		return (free_config(&data.cfg), 1);
	init_game(&data);
	mlx_hook(data.win, KEY_PRESS, KEYPRESSMASK, key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, KEYRELEASEMASK, key_release, &data);
	mlx_hook(data.win, MOTION_NOTIFY, POINTERMOTIONMASK, mouse_move, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, STRUCNOTIFYMASK, close_window, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	free_config(&data.cfg);
	return (0);
}
