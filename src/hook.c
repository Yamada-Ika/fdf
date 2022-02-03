#include "fdf.h"

void	ft_install_hook(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_key_hook, vars);
	mlx_mouse_hook(vars->win, ft_mouse_hook, vars);
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

void	ft_switch_projection(int keycode, t_vars *vars)
{
	if (keycode == I)
		ft_set_isometric(vars);
	if (keycode == P)
		ft_set_parallel(vars);
	if (keycode == C)
		ft_set_conic(vars);
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
	if (is_switch_projection_key(keycode))
		ft_switch_projection(keycode, vars);
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
	if (is_zoom_up(button, vars->zoom_rate))
		vars->zoom_rate += 0.1;
	if (is_zoom_down(button, vars->zoom_rate))
		vars->zoom_rate -= 0.1;
	if ((button == SCROLL_UP && vars->zoom_rate < 100)
		|| (button == SCROLL_DOWN && vars->zoom_rate > 0.0))
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		ft_display_map(vars);
	}
	return (0);
}
