#include "cub3d.h"

/*
 Calcule la couleur d'une étoile en fonction de sa luminosité
 brightness = Niveau de luminosité de l'étoile (0.0 à 1.0)
 retourne la couleur au format RGB encodée sur 32 bits
 
 Cette fonction génère des couleurs réalistes pour les étoiles :
 - Étoiles très brillantes (>0.8) : Blanc pur
 - Étoiles moyennement brillantes (>0.6) : Teinte bleutée
 - Étoiles faibles : Teinte jaunâtre/orangée
 */
static int	get_star_color(double brightness)
{
	int	red;
	int	green;
	int	blue;

	if (brightness > 0.8)
	{
		red = (int)(brightness * 255);
		green = (int)(brightness * 255);
		blue = (int)(brightness * 255);
	}
	else if (brightness > 0.6)
	{
		red = (int)(brightness * 255 * 0.8);
		green = (int)(brightness * 255 * 0.9);
		blue = (int)(brightness * 255);
	}
	else
	{
		red = (int)(brightness * 255);
		green = (int)(brightness * 255 * 0.9);
		blue = (int)(brightness * 255 * 0.7);
	}
	return ((red << 16) | (green << 8) | blue);
}

/*
 Initialise le système de ciel étoilé avec génération aléatoire d'étoiles
 Cette fonction met en place l'environnement du ciel étoilé :
 - Alloue la mémoire pour STAR_COUNT étoiles
 - Génère des positions aléatoires dans la moitié supérieure de l'écran
 en laissant 4 pixels de marge : rand() génère un nombre entier aléatoire
 entre 0 et RAND_MAX et % N permet de restreindre la plage à [0, N-1]
 - Assigne des propriétés aléatoires à chaque étoile :
   * Luminosité entre MIN_BRIGHTNESS et MAX_BRIGHTNESS
   * Vitesse de scintillement entre 0.01 et 0.04 (effet naturel : les
   vraies étoiles scintillent à des rythmes différents)
   * Phase de scintillement initiale entre 0 et 2π
   * Taille entre 1 et 3 pixels
 - Calcule la couleur initiale basée sur la luminosité
 */
void	init_starry_sky(t_cub *data)
{
	int	i;

	data->stars = gc_malloc(sizeof(t_star) * STAR_COUNT, &data->gc);
	i = 0;
	while (i < STAR_COUNT)
	{
		data->stars[i].x = (double)(4 + rand() % (data->img.width - 8));
		data->stars[i].y = (double)(4 + rand() % (data->img.height / 2 - 8));
		data->stars[i].brightness = MIN_BRIGHTNESS
			+ ((double)rand() / RAND_MAX) * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);
		data->stars[i].twinkle_speed = 0.01
			+ ((double)rand() / RAND_MAX) * 0.03;
		data->stars[i].twinkle_angle = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
		data->stars[i].size = 1 + (rand() % 3);
		data->stars[i].color = get_star_color(data->stars[i].brightness);
		i++;
	}
}

/*
 Met à jour l'animation des étoiles (effet de scintillement)
 Cette fonction gère l'animation continue du ciel étoilé :
 - Pour chaque étoile :
   * Met à jour sa phase de scintillement dans [0, 2π]
   * Calcule une nouvelle luminosité via une fonction sinusoïdale
   * Recalcule la couleur en fonction de la nouvelle luminosité
 */
void	update_starry_sky(t_cub *data)
{
	int		i;
	t_star	*star;
	double	sine_val;

	i = -1;
	while (++i < STAR_COUNT)
	{
		star = &data->stars[i];
		star->twinkle_angle += star->twinkle_speed;
		if (star->twinkle_angle > 2.0 * M_PI)
			star->twinkle_angle -= 2.0 * M_PI;
		sine_val = sin(star->twinkle_angle);
		star->brightness = MIN_BRIGHTNESS + (MAX_BRIGHTNESS - MIN_BRIGHTNESS)
			* ((sine_val + 1.0) / 2.0);
		star->color = get_star_color(star->brightness);
	}
}

/*
 Cette fonction rend une étoile complète en plusieurs étapes :
 - Dessine un carré plein centré sur la position de l'étoile
 - Pour les étoiles très brillantes (>0.7) et de taille >1 :
    * Ajoute une croix lumineuse pour un effet réaliste de diffraction
 */
static void	draw_star(t_cub *data, t_star *star)
{
	int	x;
	int	y;
	int	i;

	y = -star->size / 2 - 1;
	while (++y <= star->size / 2)
	{
		x = -star->size / 2 - 1;
		while (++x <= star->size / 2)
		{
			data->img.color = star->color;
			set_color_pixel(&data->img, star->x + x, star->y + y);
		}
	}
	if (star->brightness > 0.7 && star->size > 1)
	{
		i = -3;
		while (++i <= 2)
		{
			data->img.color = star->color;
			set_color_pixel(&data->img, star->x + i, star->y);
			set_color_pixel(&data->img, star->x, star->y + i);
		}
	}
}

/*
Cette fonction rend le ciel étoilé complet en deux étapes :
 - Dessine un dégradé de fond vertical du noir vers bleu foncé
 (l'intensité augmente avec la hauteur pour simuler l'atmosphère)
 - Dessine chaque étoile
 */
void	draw_starry_sky(t_cub *data)
{
	int	gradient_intensity;
	int	x;
	int	y;
	int	i;

	y = -1;
	while (++y < data->img.height / 2)
	{
		x = -1;
		gradient_intensity = (int)((double)y / (data->img.height / 2) * 30);
		data->img.color = (gradient_intensity << 16)
			| (gradient_intensity << 8) | (gradient_intensity + 20);
		while (++x < data->img.width)
			set_color_pixel(&data->img, x, y);
	}
	i = -1;
	while (++i < STAR_COUNT)
		draw_star(data, &data->stars[i]);
}
