#ifndef CUB3D_H
# define CUB3D_H

/* ================================ INCLUDES ================================ */

# include "mlx.h"
# include "libft.h"
# include "gc.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <sys/stat.h>
# include <math.h>

/* ================================ DEFINES ================================ */

# define COLOR_ENABLED 1
# if COLOR_ENABLED
#  define YELLOW 0xFFFF00
#  define GREEN 0x00FF00
#  define RED 0xFF0000
#  define CYAN 0x00AAFF
#  define BLUE 0x4169E1
#  define WHITE 0xFFFFFF
#  define BLACK 0x000000
#  define GREY 0x888888
#  define DARK_GREY 0x222222
#  define ORANGE 0xFF4500
# else
#  define YELLOW ""
#  define GREEN ""
#  define RED ""
#  define CYAN ""
#  define BLUE ""
#  define WHITE ""
#  define BLACK ""
#  define GREY ""
#  define DARK_GREY ""
#  define ORANGE ""
# endif

# define FOV 0.66
# define ANGULAR_SPEED 0.03
# define WALK_SPEED 0.03
# define DEFAULT_WIN_WIDTH 1280
# define DEFAULT_WIN_HEIGHT 720
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300
# define MENU_SIZE 500
# define BUFFER_SIZE 1024
# define OFF_X 10
# define OFF_Y 10
# define STAR_COUNT 200
# define MIN_BRIGHTNESS 0.2
# define MAX_BRIGHTNESS 1.0

/* ==================================== ENUM =================================== */

typedef enum e_keys
{
	A = 97,
	C = 99,
	D = 100,
	E = 101,
	H = 104,
	M = 109,
	N = 110,
	S = 115,
	W = 119,
	ESC = 65307,
	LEFT = 65361,
	UP = 65362,
	RIGHT = 65363,
	DOWN = 65364
}	t_keys;

typedef enum e_event
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
}	t_event;

typedef enum e_mask
{
	KEYPRESSMASK = (1L << 0),
	KEYRELEASEMASK = (1L << 1),
	POINTERMOTIONMASK = (1L << 6),
	STRUCNOTIFYMASK = (1L << 17)
}	t_mask;

typedef enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR
}	t_texture;

typedef enum e_door_state
{
	DOOR_OPEN,
	DOOR_CLOSED
}	t_door_state;

/* ================================== STRUCTURES ================================= */

typedef struct s_spawn
{
	double	x;
	double	y;
	char	direction;
}	t_spawn;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
}	t_door;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*door_texture;
	char		*starry_sky_texture;
	char		**map;
	int			floor_color;
	int			ceiling_color;
	int			map_width;
	int			map_height;
	int			door_nb;
	t_spawn		player;
	t_door		*doors;
}	t_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	bool	forward;
	bool	left;
	bool	backward;
	bool	right;
	bool	turn_left;
	bool	turn_right;
}	t_player;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		color;
}	t_image;

typedef struct s_ray
{
	double	scaled_view_x;
	double	dir_x;
	double	dir_y;
	double	step_dist_x;
	double	step_dist_y;
	double	player_side_dist_x;
	double	player_side_dist_y;
	double	player_wall_dist;
	double	wall_pos;
	double	step;
	double	tex_pos;
	bool	hit;
	bool	horiz;
	int		map_pos_x;
	int		map_pos_y;
	int		step_x;
	int		step_y;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_star
{
	double	x;
	double	y;
	double	brightness;
	double	twinkle_speed;
	double	twinkle_angle;
	int		color;
	int		size;
}	t_star;

typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_config			cfg;
	t_player			player;
	t_image				img;
	t_image				texture[5];
	t_ray				ray;
	t_star				*stars;
	bool				show_cursor;
	bool				show_minimap;
	bool				show_starry_sky;
	bool				show_help_menu;
	int					last_mouse_x;
	int					minimap_scale;
	double				animation_time;
	t_gc				gc;
}	t_cub;

/* ========================== FUNCTION PROTOTYPES =========================== */

/* --- initialization.c --- */
void	init_game(t_cub *data);

/* --- main.c --- */
int		parse_and_validate(char *filename, t_cub *data);
int		parse_until_map(char **lines, t_cub *data);

/* --- parsing/ --- */
char	*get_next_line(int fd);
char	**read_file_lines(const char *filename);
void	read_file(const char *filename);
void	remove_carriage_return(char *line);
int		check_file_valid(const char *filename);
int		parse_file(char **lines, t_cub *data);
int		parse_map(char **lines, int start_index, t_cub *data);
int		parse_line(char *line, t_cub *data);
int		parse_color(char *line, t_config *cfg);
int		all_elements_present(t_config *cfg);
int		map_has_doors(t_config *cfg);
char	*resolve_texture_path(const char *texture_path, t_gc *gc);
int		validate_texture_file(const char *texture_path);
int		is_valid_map(t_config *cfg);
int		is_map_closed(t_config *cfg);
int		has_only_valid_chars(char **map);
int		is_valid_open_spaces(char **map);
int		has_empty_line_inside(char **map);
int		init_player(t_config *cfg);
void	init_player_vectors(t_player *player, t_config *cfg);
int		has_tabs(char *line);
int		is_empty_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		first_map_line(char **lines);
int		is_map_line(char *line);
int		get_line_type(char *line);
char	**extract_map(char **lines, int start);
void	pad_map_lines(char **map, int width, t_gc *gc);
int		skip_spaces(char *line);
void	free_config(t_config *cfg);
void	free_tab(char **tab);
void	free_split(char **tab);
void	*exit_error(const char *msg, int code);
int		ft_strcmp(char *s1, char *s2);

/* --- exec/ --- */
int		key_press(int keycode, t_cub *data);
int		key_release(int keycode, t_cub *data);
int		close_window(t_cub *data);
int		mouse_move(int x, int y, t_cub *data);
void	move_player(t_cub *data, t_player *player);
void	turn(t_player *player, double angle);
int		game_loop(t_cub *data);
void	init_doors(t_cub *data);
void	interact_with_door(t_cub *data);
t_door	*find_door_at(t_cub *data, int x, int y);
int		is_door_closed(t_cub *data, int x, int y);
void	set_color_pixel(t_image *img, int x, int y);
void	draw_floor_ceiling(t_image *img, int ceiling_color, int floor_color,
			bool floor_only);
void	draw_walls(t_cub *data);
void	draw_wall_column(t_cub *data, t_ray *ray, int texture_dir, int x);
void	draw_square(t_image *img, int start_x, int start_y, int size);
void	draw_minimap(t_cub *cub);
void	init_starry_sky(t_cub *data);
void	update_starry_sky(t_cub *data);
void	draw_starry_sky(t_cub *data);
void	init_ray_dir(t_cub *data, t_player *player, int x, t_ray *ray);
void	init_dda_params(t_player *player, t_ray *ray);
void	find_wall_hit(t_cub *data, t_ray *ray);
void	calculate_wall_bounds(t_cub *data, t_player *player, t_ray *ray);
int		calculate_texture_params(t_cub *data, t_player *player, t_ray *ray);
void	draw_help_menu(t_cub *data);

/* --- utils.c --- */
int		print_help(void);
void	clean_exit(int status, t_cub *data);
void	error(const char *error_msg, int status, t_cub *data);

#endif
