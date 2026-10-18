#include "cub3d.h"

static void	load_texture_file(t_cub *data, char *path, int index)
{
	data->texture[index].ptr = mlx_xpm_file_to_image(data->mlx, path,
			&data->texture[index].width, &data->texture[index].height);
	if (!data->texture[index].ptr)
	{
		data->texture[index].ptr = NULL;
		data->texture[index].addr = NULL;
		data->texture[index].width = 0;
		data->texture[index].height = 0;
	}
	else
	{
		data->texture[index].addr = mlx_get_data_addr(data->texture[index].ptr,
				&data->texture[index].bpp, &data->texture[index].line_length,
				&data->texture[index].endian);
	}
}

static void	init_textures(t_cub *data)
{
	char	*paths[5];
	int		i;

	paths[0] = data->cfg.north_texture;
	paths[1] = data->cfg.south_texture;
	paths[2] = data->cfg.east_texture;
	paths[3] = data->cfg.west_texture;
	paths[4] = data->cfg.door_texture;
	i = -1;
	while (++i < 5)
		load_texture_file(data, paths[i], i);
}

static void	init_mlx_components(t_cub *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Failed to initialize MLX library", EXIT_FAILURE, NULL);
	data->img.width = DEFAULT_WIN_WIDTH;
	data->img.height = DEFAULT_WIN_HEIGHT;
	data->win = mlx_new_window(data->mlx, data->img.width, data->img.height,
			"Cub3D");
	if (!data->win)
		error("Failed to create window", EXIT_FAILURE, data);
	data->img.ptr = mlx_new_image(data->mlx, data->img.width, data->img.height);
	if (!data->img.ptr)
		error("Failed to create image", EXIT_FAILURE, data);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
}

static void	init_game_settings(t_cub *data)
{
	data->show_cursor = true;
	data->show_minimap = true;
	data->show_help_menu = false;
	if (MINIMAP_WIDTH / data->cfg.map_width < MINIMAP_HEIGHT
		/ data->cfg.map_height)
		data->minimap_scale = MINIMAP_WIDTH / data->cfg.map_width;
	else
		data->minimap_scale = MINIMAP_HEIGHT / data->cfg.map_height;
}

void	init_game(t_cub *data)
{
	init_mlx_components(data);
	init_game_settings(data);
	init_textures(data);
	init_player_vectors(&data->player, &data->cfg);
	init_doors(data);
	init_starry_sky(data);
}
