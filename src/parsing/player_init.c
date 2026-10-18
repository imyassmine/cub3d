#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_position(t_config *cfg, int i, int j)
{
	cfg->player.x = j + 0.5;
	cfg->player.y = i + 0.5;
	cfg->player.direction = cfg->map[i][j];
	cfg->map[i][j] = '0';
}

static int	count_and_init_players(t_config *cfg)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (cfg->map[i])
	{
		j = 0;
		while (cfg->map[i][j])
		{
			if (is_player_char(cfg->map[i][j]))
			{
				if (count == 0)
					set_player_position(cfg, i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	init_player(t_config *cfg)
{
	int	count;

	count = count_and_init_players(cfg);
	if (count != 1)
		return (0);
	return (1);
}

void	init_player_vectors(t_player *player, t_config *cfg)
{
	player->pos_x = cfg->player.x;
	player->pos_y = cfg->player.y;
	if (cfg->player.direction == 'N')
		player->dir_y = -1.0;
	else if (cfg->player.direction == 'S')
		player->dir_y = 1.0;
	else if (cfg->player.direction == 'E')
		player->dir_x = 1.0;
	else if (cfg->player.direction == 'W')
		player->dir_x = -1.0;
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}
