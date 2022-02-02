#include "fdf.h"

void	ft_install_hook(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_key_hook, vars);
	mlx_mouse_hook(vars->win, ft_mouse_hook, vars);
}

static bool	is_valid_keycode(int keycode)
{
	return ((keycode == RIGHT || keycode == LEFT
			|| keycode == UP || keycode == DOWN
			|| keycode == I || keycode == P
			|| keycode == C));
}

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == RIGHT)
		vars->shift_x += 5;
	if (keycode == LEFT)
		vars->shift_x -= 5;
	if (keycode == UP)
		vars->shift_y -= 5;
	if (keycode == DOWN)
		vars->shift_y += 5;
	if (keycode == I)
		ft_set_isometric(vars);
	if (keycode == P)
		ft_set_parallel(vars);
	if (keycode == C)
		ft_set_conic(vars);
	if (is_valid_keycode(keycode))
		ft_display_map(vars);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_vars *vars)
{
	x = y;
	if (button == SCROLL_UP && vars->zoom_rate < 100)
		vars->zoom_rate += 0.1;
	if (button == SCROLL_DOWN && vars->zoom_rate > 0.1)
		vars->zoom_rate -= 0.1;
	if ((button == SCROLL_UP && vars->zoom_rate < 100)
		|| (button == SCROLL_DOWN && vars->zoom_rate > 0.0))
	{
		ft_display_map(vars);
	}
	return (0);
}
