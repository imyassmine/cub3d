#include "cub3d.h"

// free une texture si elle est allouée
static void	free_texture(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

// free toute la structure t_config (textures, map)
void	free_config(t_config *cfg)
{
	free_texture(&cfg->north_texture);
	free_texture(&cfg->south_texture);
	free_texture(&cfg->west_texture);
	free_texture(&cfg->east_texture);
	free_texture(&cfg->door_texture);
	free_tab(cfg->map);
}
