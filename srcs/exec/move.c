/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 04:02:47 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/01 22:28:00 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_fb(t_player *player, t_config *cfg)
{
	double	mv;
	double	new_x;
	double	new_y;
	int		dir;

	if (player->forward)
		dir = 1;
	else if (player->backward)
		dir = -1;
	mv = WALK_SPEED * dir;
	new_x = player->pos_x + player->dir_x * mv;
	if (cfg->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	new_y = player->pos_y + player->dir_y * mv;
	if (cfg->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

static void	move_strafe(t_player *player, t_config *cfg)
{
	double	mv;
	double	new_x;
	double	new_y;
	int		dir;

	if (player->left)
		dir = -1;
	else if (player->right)
		dir = +1;
	mv = WALK_SPEED * dir;
	new_x = player->pos_x - player->dir_y * mv;
	if (cfg->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	new_y = player->pos_y + player->dir_x * mv;
	if (cfg->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}
/*
dir_x = dir cos(α)
dir_y = dir sin(α)
turn left	-> rotation de θ dans le sens anti-horaire
			-> vitesse de rotation positive
/!\ y augmente vers le bas donc visuellement rotation de θ dans le sens horaire
			-> inverser le signe de de θ
new_dir_x 	= dir cos(α + θ)
			= dir cos(α) cos(θ) - dir sin(α) sin(θ)
			= dir_x cos(θ) - dir_y sin(θ)
new_dir_y 	= dir sin(α + θ)
 			= dir sin(α) cos(θ) + dir cos(α) sin(θ)
			= dir_y cos(θ) + dir_x sin(θ)
*/

void	turn(t_player *player, double angle)
{
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	new_dir_x = player->dir_x * cos(angle)
		- player->dir_y * sin(angle);
	new_dir_y = player->dir_y * cos(angle)
		+ player->dir_x * sin(angle);
	player->dir_x = new_dir_x;
	player->dir_y = new_dir_y;
	new_plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	new_plane_y = player->plane_y * cos(angle)
		+ player->plane_x * sin(angle);
	player->plane_x = new_plane_x;
	player->plane_y = new_plane_y;
}

void	move_player(t_cub *data, t_player *player)
{
	if (player->forward == true && player->backward == true)
		return ;
	if (player->left == true && player->right == true)
		return ;
	if (player->turn_left == true && player->turn_right == true)
		return ;
	if (player->forward == true || player->backward == true)
		move_fb(player, &data->cfg);
	if (player->left == true || player->right == true)
		move_strafe(player, &data->cfg);
	if (player->turn_left == true)
		turn(player, -ANGULAR_SPEED);
	if (player->turn_right == true)
		turn(player, +ANGULAR_SPEED);
}
