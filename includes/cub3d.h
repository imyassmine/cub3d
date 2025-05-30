#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */

# include "mlx.h"
# include "libft.h"
# include "gc.h"
# include "utils.h"
# include "line_utils.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

/* -------------------------------------------------------------------------- */
/*                                  DEFINES                                   */
/* -------------------------------------------------------------------------- */

// COLORS
# define COLOR_ENABLED 1
# if COLOR_ENABLED
#  define DEFAULT "\001\033[0m"
#  define RED "\001\033[1;31m"
#  define GREEN "\033[1;32m\002"
#  define YELLOW "\001\033[1;33m"
#  define BLUE "\001\033[1;34m"
#  define MAGENTA "\001\033[1;35m"
#  define ROSE "\001\033[1;95m"
#  define CYAN "\033[1;36m\002"
#  define WHITE "\001\033[1;37m"
# else
#  define DEFAULT ""
#  define RED ""
#  define GREEN ""
#  define YELLOW ""
#  define BLUE ""
#  define MAGENTA ""
#  define ROSE ""
#  define CYAN ""
#  define WHITE ""
# endif

# define BUFFER_SIZE		42

// PLAYER MOVEMENT PARAMETERS
# define WALK_SPEED			0.04
# define ROTATION_SPEED		0.04	// rotation speed in radians

// WINDOW PARAMETERS
# define FOV				0.66	// Field of view in radians (120 degrees)

/* -------------------------------------------------------------------------- */
/*                                   ENUMS                                    */
/* -------------------------------------------------------------------------- */

// EVENT TYPES ENUM
typedef enum e_event_type
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
}	t_event_type;

// EVENT MASKS ENUM
typedef enum e_event_mask
{
	KEYPRESSMASK = 1,
	KEYRELEASEMASK = 2,
	POINTERMOTIONMASK = 64,
	STRUCNOTIFYMASK = 131072
}	t_event_mask;

// KEY CODES ENUM
typedef enum e_keys
{
	KEY_SPACE = 32,
	PLUS = 61,
	A = 97,
	C = 99,
	D = 100,
	H = 104,
	R = 114,
	S = 115,
	W = 119,
	ESC = 65307,
	LEFT = 65361,
	UP = 65362,
	RIGHT = 65363,
	DOWN = 65364,
	SHIFT = 65505
}	t_keys;

/* -------------------------------------------------------------------------- */
/*                                 STRUCTURES                                 */
/* -------------------------------------------------------------------------- */

// CONFIGURATION STRUCTURE
typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;

	int			floor_color;
	int			ceiling_color;

	char		**map;				// 2D array representing the map
	int			map_width;
	int			map_height;

	int			player_start_x;
	int			player_start_y;
	char		player_dir;			// 'N','S','E' ou 'W'
}	t_config;

// IMAGE BUFFER STRUCTURE
typedef struct s_image
{
	void		*ptr;
	char		*addr;
	int			bpp;				// bits per pixel
	int			line_length;		// bytes per line
	int			endian;				// byte-order (0 or 1)
	int			width;
	int			height;
}	t_image;

typedef struct s_player
{
	bool		forward;
	bool		left;
	bool		backward;
	bool		right;
	bool		turn_left;
	bool		turn_right;
	double		pos_x;				// Player's X position
	double		pos_y;
	double		dir_x;				// Player's direction vector X
	double		dir_y;
	double		plane_x;			// Camera plane X (perpendicular to dir)
	double		plane_y;
}	t_player;

// GAME CONTEXT STRUCTURE
typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_config	cfg;
	t_image		img;
	t_player	player;
	bool		cursor_visible;
	int			last_mouse_x;
	t_gc		gc;
}	t_cub;

/* -------------------------------------------------------------------------- */
/*                             FUNCTION PROTOTYPES                            */
/* -------------------------------------------------------------------------- */

/* ----------------------------- Initialization ----------------------------- */
void	init_game(t_cub *data);

/* -------------------------------- Parser ---------------------------------- */

// LECTURE DE FICHIER
char	**read_file_lines(char *filename);
void	read_file(const char *filename);
int		count_lines(const char *filename);
char	**load_lines(const char *filename, int count);

// PARSING DES LIGNES
int		parse_line(char *line, t_config *cfg);
int		parse_color(char *line, t_config *cfg);
int		parse_map(char **lines, int start_index, t_config *cfg);

// VALIDATION DE LA MAP
int		is_valid_map(t_config *cfg);
int		is_map_closed(t_config *cfg);
int		has_only_valid_chars(char **map);

/* ------------------------------- Executor --------------------------------- */

// EVENTS HANDLERS
int		key_press(int keycode, t_cub *data);
int		key_release(int keycode, t_cub *data);
int		close_window(t_cub *data);
int		mouse_move(int x, int y, t_cub *data);

// PLAYER MOVEMENT
void	move_player(t_cub *data, t_player *player);
void	turn_left(t_player *player);
void	turn_right(t_player *player);

// RAY CASTING
int		game_loop(t_cub *data);
void	render_walls(t_cub *data);
void	fontion_temporaire(const char *filename, t_cub *data);

/* ------------------------------- Utilities -------------------------------- */
int		print_help(void);
void	clean_exit(int status, t_cub *data);
void	error(const char *error_msg, int status, t_cub *game);
#endif
