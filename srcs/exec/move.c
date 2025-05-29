/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 04:02:47 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/29 19:31:50 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_fb(t_player *player, t_config *cfg)
{
	double	mv;
	double	new_x;
	double	new_y;
	int		dir;

	// Si le joueur appuie à la fois sur avancer et reculer, on ne fait rien
	if (player->forward && player->backward)
		return ;
	else if (player->forward)
		dir = 1; // Avancer
	else if (player->backward)
		dir = -1; // Reculer
	mv = WALK_SPEED * dir; // Vitesse de déplacement
	new_x = player->pos_x + player->dir_x * mv; // Nouvelle position en x
	if (cfg->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x; // si la case n'est pas un mur
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

	if (player->left && player->right)
		return ;
	else if (player->left)
		dir = -1;
	else if (player->right)
		dir = +1;
	mv = WALK_SPEED * dir;
	new_x = player->pos_x + player->plane_x * mv;
	if (cfg->map[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	new_y = player->pos_y + player->plane_y * mv;
	if (cfg->map[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}
/*
dir_x = dir cos(α)
dir_y = dir sin(α)
turn left -> rotation de θ dans le sens antihoraire
new_dir_x 	= dir cos(α + θ)
			= dir cos(α) cos(θ) - dir sin(α) sin(θ)
			= dir_x cos(θ) - dir_y sin(θ)
new_dir_y 	= dir sin(α + θ)
 			= dir sin(α) cos(θ) + dir cos(α) sin(θ)
			= dir_y cos(θ) + dir_x sin(θ)
*/

static void	turn_left(t_player *player)
{
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	new_dir_x = player->dir_x * cos(ROTATION_SPEED)
		- player->dir_y * sin(ROTATION_SPEED);
	new_dir_y = player->dir_y * cos(ROTATION_SPEED)
		+ player->dir_x * sin(ROTATION_SPEED);
	player->dir_x = new_dir_x;
	player->dir_y = new_dir_y;
	new_plane_x = player->plane_x * cos(ROTATION_SPEED)
		- player->plane_y * sin(ROTATION_SPEED);
	new_plane_y = player->plane_y * cos(ROTATION_SPEED)
		+ player->plane_x * sin(ROTATION_SPEED);
	player->plane_x = new_plane_x;
	player->plane_y = new_plane_y;
}

static void	turn_right(t_player *player)
{
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	new_dir_x = player->dir_x * cos(ROTATION_SPEED)
		+ player->dir_y * sin(ROTATION_SPEED);
	new_dir_y = player->dir_y * cos(ROTATION_SPEED)
		- player->dir_x * sin(ROTATION_SPEED);
	player->dir_x = new_dir_x;
	player->dir_y = new_dir_y;
	new_plane_x = player->plane_x * cos(ROTATION_SPEED)
		+ player->plane_y * sin(ROTATION_SPEED);
	new_plane_y = player->plane_y * cos(ROTATION_SPEED)
		- player->plane_x * sin(ROTATION_SPEED);
	player->plane_x = new_plane_x;
	player->plane_y = new_plane_y;
}

void	move_player(t_cub *data, t_player *player)
{
	if (player->forward || player->backward)
		move_fb(player, &data->cfg);
	else if (player->left || player->right)
		move_strafe(player, &data->cfg);
	else if (player->turn_left)
		turn_left(player);
	else if (player->turn_right)
		turn_right(player);
}
