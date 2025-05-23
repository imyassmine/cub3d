/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:03:50 by yaabdall          #+#    #+#             */
/*   Updated: 2025/05/23 19:59:40 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include "get_next_line_bonus.h"
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
	KEY_ESC = 65307,
	LEFT = 65361,
	UP = 65362,
	RIGHT = 65363,
	DOWN = 65364,
	SHIFT = 65505
}	t_keys;

/* -------------------------------------------------------------------------- */
/*                                 STRUCTURES                                 */
/* -------------------------------------------------------------------------- */

// IMAGE STRUCTURE
typedef struct s_image
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
	int					width;
	int					height;
}	t_image;

// DATA STRUCTURE
typedef struct s_cub
{
	t_image				img;
	t_gc				gc;
}	t_cub;

/* -------------------------------------------------------------------------- */
/*                             FUNCTION PROTOTYPES                            */
/* -------------------------------------------------------------------------- */

/* ----------------------------- Initialization ----------------------------- */
void	data_init(int argc, char **argv, t_cub *data);

/* -------------------------------- Parser ---------------------------------- */

/* ------------------------------- Executor --------------------------------- */

/* ------------------------------- Utilities -------------------------------- */

#endif
