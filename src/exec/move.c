#include "cub3d.h"

/*
 Vérifie si une position donnée est accessible pour le joueur
 data = Structure principale contenant la configuration du jeu
 x = Coordonnée x de la position à vérifier
 y = Coordonnée y de la position à vérifier
 retourne 1 si la position est accessible, 0 sinon
 
 Une position est considérée comme accessible si :
 - Elle est dans les limites de la carte
 - Elle correspond à un espace vide ('0')
 - Elle correspond à une porte ouverte ('D' avec état DOOR_OPEN)
 */
static int	is_position_walkable(t_cub *data, int x, int y)
{
	t_door	*door;

	if (x < 0 || x >= data->cfg.map_width || y < 0 || y >= data->cfg.map_height)
		return (0);
	if (data->cfg.map[y][x] == '0')
		return (1);
	if (data->cfg.map[y][x] == 'D')
	{
		door = find_door_at(data, x, y);
		return (door && door->state == DOOR_OPEN);
	}
	return (0);
}

/*
 Gère le mouvement avant/arrière du joueur
 player = Pointeur vers la structure du joueur
 data = Structure principale contenant les données du jeu
 
 Cette fonction calcule le nouveau position du joueur lors d'un mouvement
 avant ou arrière en utilisant le vecteur de direction. Elle vérifie
 la collision avec les murs avant d'effectuer le déplacement.
 Le mouvement se fait selon l'axe de vision du joueur (dir_x, dir_y).
 */
static void	move_fb(t_player *player, t_cub *data)
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
	if (is_position_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	new_y = player->pos_y + player->dir_y * mv;
	if (is_position_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

/*
 Gère le mouvement latéral (strafe) du joueur
 player = Pointeur vers la structure du joueur
 data = Structure principale contenant les données du jeu
 
 Cette fonction permet au joueur de se déplacer latéralement (gauche/droite)
 sans changer sa direction de vision. Le mouvement se fait perpendiculairement
 au vecteur de direction en utilisant le vecteur perpendiculaire (-dir_y, dir_x).
 Elle vérifie également les collisions avant d'effectuer le déplacement.
 */
static void	move_strafe(t_player *player, t_cub *data)
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
	if (is_position_walkable(data, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	new_y = player->pos_y + player->dir_x * mv;
	if (is_position_walkable(data, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

/* Effectue une rotation du vecteur de direction du joueur
et de son plan de vision
player = Pointeur vers la structure du joueur
angle = Angle de rotation en radians
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

/*
Fonction principale de gestion du mouvement du joueur
data = Structure principale contenant les données du jeu
player = Pointeur vers la structure du joueur

Cette fonction coordonne tous les types de mouvement du joueur :
- Mouvement avant/arrière (move_fb)
- Mouvement latéral/strafe (move_strafe)
- Rotation gauche/droite (turn)

Elle gère les conflits de commandes (ex: avant + arrière simultanément)
en les annulant. Les mouvements sont appliqués selon les flags booléens
de la structure player qui sont mis à jour par les événements clavier.
*/
void	move_player(t_cub *data, t_player *player)
{
	if (player->forward == true && player->backward == true)
		return ;
	if (player->left == true && player->right == true)
		return ;
	if (player->turn_left == true && player->turn_right == true)
		return ;
	if (player->forward == true || player->backward == true)
		move_fb(player, data);
	if (player->left == true || player->right == true)
		move_strafe(player, data);
	if (player->turn_left == true)
		turn(player, -ANGULAR_SPEED);
	if (player->turn_right == true)
		turn(player, +ANGULAR_SPEED);
}
