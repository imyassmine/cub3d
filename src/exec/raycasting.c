#include "cub3d.h"

/*
Cette fonction initialise les paramètres du rayon pour la colonne x :
- Normalise la position x de l'écran dans l'intervalle [-1, 1]
- Calcule la direction du rayon en fonction de la position du
joueur et de son plan de vue
- Définit la position de la case de la map où le rayon commence
*/
void	init_ray_dir(t_cub *data, t_player *player, int x, t_ray *ray)
{
	ray->scaled_view_x = 2 * x / (double)data->img.width - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->scaled_view_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->scaled_view_x;
	ray->map_pos_x = (int)player->pos_x;
	ray->map_pos_y = (int)player->pos_y;
	ray->step_dist_x = fabs(1.0 / ray->dir_x);
	ray->step_dist_y = fabs(1.0 / ray->dir_y);
}

/*
- Calcule la distance que le rayon doit parcourir pour traverser
une case complète dans chaque direction
- Détermine la direction du pas (step) dans chaque direction
- Calcule la distance du joueur au bord de la case de la map
*/
void	init_dda_params(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->player_side_dist_x = (player->pos_x - ray->map_pos_x)
			* ray->step_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->player_side_dist_x = (ray->map_pos_x + 1.0 - player->pos_x)
			* ray->step_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->player_side_dist_y = (player->pos_y - ray->map_pos_y)
			* ray->step_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->player_side_dist_y = (ray->map_pos_y + 1.0 - player->pos_y)
			* ray->step_dist_y;
	}
}

/*
Algorithme DDA pour trouver le premier mur touché par le rayon :
- Avance case par case en choisissant toujours la frontière la plus proche
- horiz indique le type de frontière traversée :
  * false (0) = frontière verticale (murs EST/OUEST)
  * true (1) = frontière horizontale (murs NORD/SUD)
- S'arrête dès qu'un mur ('1') ou une porte fermée ('D') est trouvé
*/
void	find_wall_hit(t_cub *data, t_ray *ray)
{
	ray->hit = false;
	while (ray->hit == false)
	{
		if (ray->player_side_dist_x < ray->player_side_dist_y)
		{
			ray->player_side_dist_x += ray->step_dist_x;
			ray->map_pos_x += ray->step_x;
			ray->horiz = false;
		}
		else
		{
			ray->player_side_dist_y += ray->step_dist_y;
			ray->map_pos_y += ray->step_y;
			ray->horiz = true;
		}
		if (data->cfg.map[ray->map_pos_y][ray->map_pos_x] == '1')
			ray->hit = true;
		else if (data->cfg.map[ray->map_pos_y][ray->map_pos_x] == 'D')
		{
			if (is_door_closed(data, ray->map_pos_x, ray->map_pos_y))
				ray->hit = true;
		}
	}
}

/*
(1 - ray->step_x) / 2.0 = 0 ou 1 indiquant la face gauche ou droite de la case
Si un mur etait a distance 1.0, il occuperait toute la hauteur de l'ecran :
Taille_apparente = Taille_référence / Distance
Repartit le mur de manière à ce qu'il soit centré sur l'écran
Pour le cas d'un mur très proche (player_wall_dist < 1.0), on clippe aux bords
pour éviter de dessiner en dehors des limites de l'écran
*/
void	calculate_wall_bounds(t_cub *data, t_player *player, t_ray *ray)
{
	if (ray->horiz == false)
		ray->player_wall_dist = (ray->map_pos_x - player->pos_x + (1
					- ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->player_wall_dist = (ray->map_pos_y - player->pos_y + (1
					- ray->step_y) / 2.0) / ray->dir_y;
	ray->wall_height = (int)(data->img.height / ray->player_wall_dist);
	ray->draw_start = data->img.height / 2 - ray->wall_height / 2;
	ray->draw_end = data->img.height / 2 + ray->wall_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= data->img.height)
		ray->draw_end = data->img.height - 1;
}

/*
ray->wall_pos est la position d'impact du rayon sur le mur :
Position = Origine + Distance × Direction
On garde la partie fractionnaire de la position pour le calcul de la texture
Les mur EST et NORD sont "retournées" pour que la texture soit orientée
correctement
*/

int	calculate_texture_params(t_cub *data, t_player *player, t_ray *ray)
{
	int	texture_dir;

	if (data->cfg.map[ray->map_pos_y][ray->map_pos_x] == 'D')
		texture_dir = DOOR;
	else if (ray->horiz == false && ray->dir_x > 0)
		texture_dir = EAST;
	else if (ray->horiz == false)
		texture_dir = WEST;
	else if (ray->dir_y > 0)
		texture_dir = SOUTH;
	else
		texture_dir = NORTH;
	if (ray->horiz == false)
		ray->wall_pos = player->pos_y + ray->player_wall_dist * ray->dir_y;
	else
		ray->wall_pos = player->pos_x + ray->player_wall_dist * ray->dir_x;
	ray->wall_pos -= floor(ray->wall_pos);
	ray->tex_x = (int)(ray->wall_pos * data->texture[texture_dir].width);
	if ((ray->horiz == false && ray->dir_x > 0) || (ray->horiz == true
			&& ray->dir_y < 0))
		ray->tex_x = data->texture[texture_dir].width - ray->tex_x - 1;
	return (texture_dir);
}
