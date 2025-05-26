/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:03:50 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/26 22:30:51 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */

# include "mlx.h"
# include "gc.h"
# include <fnmatch.h>
# include <termios.h>
# include <signal.h>
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

// SCALING PARAMETERS
# define MOVE_STEP			1.0
# define ZOOM_FACTOR		1.2
# define SCALE_ITERATION	5

/* -------------------------------------------------------------------------- */
/*                                   ENUMS                                    */
/* -------------------------------------------------------------------------- */

// EVENT TYPES ENUM
typedef enum e_event_type
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	BUTTON_PRESS = 4,
	BUTTON_RELEASE = 5,
	DESTROY_NOTIFY = 17
}	t_event_type;

// EVENT MASKS ENUM
typedef enum e_event_mask
{
	KEYPRESSMASK = 1,
	KEYRELEASEMASK = 2,
	BUTTONPRESSMASK = 4,
	BUTTONRELEASEMASK = 8,
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

// IMAGE BUFFER STRUCTURE
typedef struct s_image
{
	void				*ptr;
	char				*addr;
	int					bpp;			// bits per pixel
	int					line_length;	// bytes per line
	int					endian;			// byte-order (0 or 1)
	int					width;
	int					height;
}	t_image;

// GAME CONTEXT STRUCTURE
typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_image				img;
	t_gc				gc;
	int					width;
	int					height;
	int					floor_color;
	int					ceiling_color;
	char				**map;			// 2D array representing the map
}	t_cub;

/* -------------------------------------------------------------------------- */
/*                             FUNCTION PROTOTYPES                            */
/* -------------------------------------------------------------------------- */

/* ----------------------------- Initialization ----------------------------- */
void	init_game(t_cub *data);

/* -------------------------------- Parser ---------------------------------- */

/* ------------------------------- Executor --------------------------------- */

// EVENTS HANDLERS
int		key_press(int keycode, t_cub *data);
int		close_window(t_cub *data);

/* ------------------------------- Utilities -------------------------------- */
void	print_help(void);
void	clean_exit(int status, t_cub *data);
void	error(const char *error_msg, int status, t_cub *game);
#endif
