/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:06:43 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/26 22:30:13 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;

	if (argc != 2)
		error("Invalid number of arguments.", 2, NULL);
	if (argc == 2 && !ft_strncmp(argv[1], "--help", 6) && !argv[1][6])
	{
		print_help();
		exit(0);
	}
	init_game(&data);
	// render(&data);
	mlx_hook(data.win, KEY_PRESS, KEYPRESSMASK, key_press, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, STRUCNOTIFYMASK, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
