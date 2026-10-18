#include "cub3d.h"

void	set_color_pixel(t_image *img, int x, int y)
{
	int	pixel;

	pixel = (y * img->line_length) + (x * img->bpp / 8);
	*(unsigned int *)(img->addr + pixel) = img->color;
}

void	draw_square(t_image *img, int start_x, int start_y, int size)
{
	int	i;
	int	j;

	j = -1;
	while (++j < size)
	{
		i = -1;
		while (++i < size)
			set_color_pixel(img, start_x + i, start_y + j);
	}
}

void	draw_floor_ceiling(t_image *img, int ceiling_color, int floor_color,
		bool floor_only)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->height)
	{
		if (floor_only && y < img->height / 2)
			continue ;
		if (y < img->height / 2)
			img->color = ceiling_color;
		else
			img->color = floor_color;
		x = -1;
		while (++x < img->width)
			set_color_pixel(img, x, y);
	}
}

/*
 Cette fonction dessine dessine le mur avec la bonne texture :
 - Le modulo fait "boucler" la texture car le mur peut être plus grand
 que la texture
 - tex_pos est la position flottante qui parcourt la texture (s'incremente de
 ray->step a chaque pixel)
 - tex_y est la coordonnée reelle du pixel dans la texture (entre 0 et height-1)
*/
void	draw_wall_column(t_cub *data, t_ray *ray, int texture_dir, int x)
{
	t_image	*tex;
	int		y;
	int		tex_y;
	double	tex_pos;
	double	step;

	tex = &data->texture[texture_dir];
	if (ray->wall_height <= 0)
		return ;
	step = (double)tex->height / ray->wall_height;
	tex_pos = (ray->draw_start - data->img.height / 2 + ray->wall_height / 2)
		* step;
	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		data->img.color = *(unsigned int *)(tex->addr + tex_y * tex->line_length
				+ ray->tex_x * tex->bpp / 8);
		set_color_pixel(&data->img, x, y);
	}
}

void	draw_walls(t_cub *data)
{
	int	texture_dir;
	int	x;

	x = -1;
	while (++x < data->img.width)
	{
		init_ray_dir(data, &data->player, x, &data->ray);
		init_dda_params(&data->player, &data->ray);
		find_wall_hit(data, &data->ray);
		calculate_wall_bounds(data, &data->player, &data->ray);
		texture_dir = calculate_texture_params(data, &data->player, &data->ray);
		draw_wall_column(data, &data->ray, texture_dir, x);
	}
}
