#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "utils.h"
# include "line_utils.h"

# define BUFFER_SIZE 42

// ─────────────────────────────────────────────────────────────
// STRUCTURES
// ─────────────────────────────────────────────────────────────

typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
}	t_player;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;

	int		floor_color;
	int		ceiling_color;

	char	**map;
	int		map_width;
	int		map_height;

	t_player	player;
}	t_config;


// ─────────────────────────────────────────────────────────────
// LECTURE DE FICHIER
// ─────────────────────────────────────────────────────────────

char	**read_file_lines(const char *filename);
void	read_file(const char *filename);
int		count_lines(const char *filename);
char	**load_lines(const char *filename, int count);


// ─────────────────────────────────────────────────────────────
// PARSING DU FICHIER COMPLET
// ─────────────────────────────────────────────────────────────

int		parse_file(char **lines, t_config *cfg);
int		parse_map(char **lines, int start_index, t_config *cfg);


// ─────────────────────────────────────────────────────────────
// PARSING DES LIGNES
// ─────────────────────────────────────────────────────────────

int		parse_line(char *line, t_config *cfg);
int		parse_color(char *line, t_config *cfg);
int		all_elements_present(t_config *cfg);


// ─────────────────────────────────────────────────────────────
// VALIDATION DE LA MAP
// ─────────────────────────────────────────────────────────────

int		is_valid_map(t_config *cfg);
int		is_map_closed(t_config *cfg);
int		has_only_valid_chars(char **map);
int		is_valid_open_spaces(char **map);
int		has_empty_line_inside(char **map);
int		init_player(t_config *cfg);


// ─────────────────────────────────────────────────────────────
// OUTILS SUR LES LIGNES
// ─────────────────────────────────────────────────────────────

int		has_tab(char *line);
int	has_tabs(char *line);
int		is_empty_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);


// ─────────────────────────────────────────────────────────────
// OUTILS SUR LA MAP
// ─────────────────────────────────────────────────────────────

int		first_map_line(char **lines);
char	**extract_map(char **lines, int start);

//à trier
void remove_carriage_return(char *line);
void	free_config(t_config *cfg);

#endif
