#include "cub3d.h"

static void	draw_help_menu_head(t_cub *data)
{
	int	menu_x;
	int	menu_y;

	menu_x = (data->img.width - MENU_SIZE) / 2;
	menu_y = (data->img.height - MENU_SIZE) / 2;
	data->img.color = WHITE;
	draw_square(&data->img, menu_x - 2, menu_y - 2, MENU_SIZE + 4);
	data->img.color = BLACK;
	draw_square(&data->img, menu_x, menu_y, MENU_SIZE);
	mlx_string_put(data->mlx, data->win, menu_x + 180, menu_y + 40,
		CYAN, "CONTROLS HELP");
	mlx_string_put(data->mlx, data->win, menu_x + 50, menu_y + 80,
		WHITE, "MOVEMENT:");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 100,
		WHITE, "W / UP    - Move forward");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 120,
		WHITE, "S / DOWN  - Move backward");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 140,
		WHITE, "A         - Strafe left");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 160,
		WHITE, "D         - Strafe right");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 180,
		WHITE, "LEFT      - Turn left");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 200,
		WHITE, "RIGHT     - Turn right");
}

void	draw_help_menu(t_cub *data)
{
	int	menu_x;
	int	menu_y;

	draw_help_menu_head(data);
	menu_x = (data->img.width - MENU_SIZE) / 2;
	menu_y = (data->img.height - MENU_SIZE) / 2;
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 220,
		WHITE, "MOUSE     - Look around");
	mlx_string_put(data->mlx, data->win, menu_x + 50, menu_y + 260,
		WHITE, "ACTIONS:");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 280,
		WHITE, "E         - Open/Close doors");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 300,
		WHITE, "C         - Toggle cursor visibility");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 320,
		WHITE, "M         - Toggle minimap");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 340,
		WHITE, "N         - Toggle starry sky");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 360,
		WHITE, "H         - Toggle this help menu");
	mlx_string_put(data->mlx, data->win, menu_x + 70, menu_y + 380,
		WHITE, "ESC       - Exit game");
	mlx_string_put(data->mlx, data->win, menu_x + 100, menu_y + 420,
		CYAN, "Press H again to close this menu");
}
