#include "fdf.h"

void	ft_install_hook(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_key_hook, vars);
	mlx_mouse_hook(vars->win, ft_mouse_hook, vars);
}

static bool	is_shift_key(int keycode)
{
	return ((keycode == RIGHT || keycode == LEFT
			|| keycode == UP || keycode == DOWN));
}

static bool	is_switch_projection_key(int keycode)
{
	return ((keycode == I || keycode == P
			|| keycode == C));
}

static bool	is_valid_key(int keycode)
{
	return (is_shift_key(keycode)
			|| is_switch_projection_key(keycode));
}

void	ft_incre_or_decre_shift_var(int keycode, int *x, int *y)
{
	if (keycode == RIGHT)
		*x += 5;
	if (keycode == LEFT)
		*x -= 5;
	if (keycode == UP)
		*y -= 5;
	if (keycode == DOWN)
		*y += 5;
}

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_loop_end(vars->mlx);
	}
	if (is_shift_key(keycode))
		ft_incre_or_decre_shift_var(keycode, &(vars->shift_x), &(vars->shift_y));
	if (keycode == I)
		ft_set_isometric(vars);
	if (keycode == P)
		ft_set_parallel(vars);
	if (keycode == C)
		ft_set_conic(vars);
	if (is_valid_key(keycode))
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		ft_display_map(vars);
	}
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
		mlx_destroy_image(vars->mlx, vars->img.img);
		ft_display_map(vars);
	}
	return (0);
}
