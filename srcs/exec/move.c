/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 04:02:47 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/28 05:07:14 by yaabdall         ###   ########.fr       */
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
		return;
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

	// Si le joueur appuie à la fois sur droite et gauche, on ne fait rien
	if (player->left && player->right)
		return;
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

static void	turn_left(t_player *player)
{
	double	save_dir_x;
	double	save_plane_x;

	save_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-TURN_SPEED)
		- player->dir_y * sin(-TURN_SPEED);
	player->dir_y = save_dir_x * sin(-TURN_SPEED)
		+ player->dir_y * cos(-TURN_SPEED);
	save_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-TURN_SPEED)
		- player->plane_y * sin(-TURN_SPEED);
	player->plane_y = save_plane_x * sin(-TURN_SPEED)
		+ player->plane_y * cos(-TURN_SPEED);
}

static void	turn_right(t_player *player)
{
	double	save_dir_x;
	double	save_plane_x;

	save_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(TURN_SPEED)
		- player->dir_y * sin(TURN_SPEED);
	player->dir_y = save_dir_x * sin(TURN_SPEED)
		+ player->dir_y * cos(TURN_SPEED);
	save_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(TURN_SPEED)
		- player->plane_y * sin(TURN_SPEED);
	player->plane_y = save_plane_x * sin(TURN_SPEED)
		+ player->plane_y * cos(TURN_SPEED);
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
