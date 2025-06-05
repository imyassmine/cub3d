/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 00:35:28 by yaabdall          #+#    #+#             */
/*   Updated: 2025/06/05 05:17:34 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	cast_ray(t_cub *data, t_player *player, int x)
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_dist;
	double		wall_x;
	double		step;
	double		tex_pos;
	bool		hit;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			y;
	int			texture_dir;
	int			tex_x;
	int			tex_y;

	// Préparation du rayon
	// Normalise la coordonnée x de l'écran dans l'intervalle [-1, 1]
	camera_x = 2 * x / (double)data->img.width - 1;
	// Calcule la direction du rayon en combinant la direction du joueur
	// et le plan de la caméra
	ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray_dir_y = player->dir_y + player->plane_y * camera_x;
	// Initialisation des variables de DDA
	// Position du joueur dans la grille de la map
	map_x = (int)player->pos_x;
	map_y = (int)player->pos_y;
	// Calcul de la distance que le rayon doit parcourir
	// pour traverser un carré de la grille
	delta_dist_x = fabs(1.0 / ray_dir_x);
	delta_dist_y = fabs(1.0 / ray_dir_y);
	// Calcul des distances initiales et directions
	// Selon le signe de la direction du rayon
	if (ray_dir_x < 0)
	{
		step_x = -1; // Le rayon va vers la gauche/haut
		// Calcul de la distance jusqu'au premier mur
		side_dist_x = (player->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1; // Le rayon va vers la droite/bas
		// Calcul de la distance jusqu'au premier mur
		side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1; // direction du rayon (-1 = gauche/haut)
		// Calcul de la distance jusqu'à la prochaine ligne horizontale
		side_dist_y = (player->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1; // direction du rayon (1 = droite/bas)
		// Calcul de la distance jusqu'à la prochaine ligne horizontale
		side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
	}
	// Boucle DDA pour trouver le mur le plus proche
	hit = 0; // Etat du rayon (0 = pas de collision, 1 = collision)
	while (hit == false)
	{
		// Le rayon avance case par case jusqu'à trouver un mur
		// À chaque étape, on choisit la direction qui nécessite le moins de distance
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // mur vertical
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // mur horizontal
		}
		if (data->cfg.map[map_y][map_x] != '0')
			hit = 1;
	}
	// Calcul de la distance perpendiculaire au mur
	if (side == 0)
		perp_dist = (map_x - player->pos_x + (1 - step_x) / 2.0) / ray_dir_x;
	else
		perp_dist = (map_y - player->pos_y + (1 - step_y) / 2.0) / ray_dir_y;
	// Calcul de la hauteur du mur à dessiner
	line_h = (int)(data->img.height / perp_dist);
	// Calcul des positions de début et de fin du mur
	// pour centrer le mur sur l'écran
	draw_start = data->img.height / 2 - line_h / 2;
	draw_end = data->img.height / 2 + line_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= data->img.height)
		draw_end = data->img.height - 1;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			texture_dir = WEST;
		else
			texture_dir = EAST;
	}
	else
	{
		if (ray_dir_y > 0)
			texture_dir = SOUTH;
		else
			texture_dir = NORTH;
	}
	if (side == 0)
		wall_x = player->pos_y + perp_dist * ray_dir_y;
	else
		wall_x = player->pos_x + perp_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->texture[texture_dir].width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = data->texture[texture_dir].width - tex_x - 1;
	step = 1.0 * data->texture[texture_dir].height / line_h;
	tex_pos = (draw_start - data->img.height / 2 + line_h / 2) * step;
	y = draw_start - 1;
	while (++y < draw_end)
	{
		tex_y = (int)tex_pos & (data->texture[texture_dir].height - 1);
		tex_pos += step;
		data->texture[texture_dir].color = *(unsigned int *)(data->texture[texture_dir].addr + tex_y * data->texture[texture_dir].line_length + tex_x * data->texture[texture_dir].bpp / 8);
		data->img.color = data->texture[texture_dir].color;	
		set_color_pixel(&data->img, x, y);
	}
}

void	render_walls(t_cub *data)
{
	int	x;

	x = -1;
	while (++x < data->img.width)
		cast_ray(data, &data->player, x);
}
