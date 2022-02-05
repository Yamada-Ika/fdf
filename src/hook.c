#include "fdf.h"

void	ft_install_hook(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_key_hook, vars);
	mlx_mouse_hook(vars->win, ft_mouse_hook, vars);
}

void	ft_incre_or_decre_shift_var(int key, int *x, int *y)
{
	if (key == RIGHT)
	{
		*x = 20;
		*y = 0;
	}
	if (key == LEFT)
	{
		*x = -20;
		*y = 0;
	}
	if (key == UP)
	{
		*x = 0;
		*y = -20;
	}
	if (key == DOWN)
	{
		*x = 0;
		*y = 20;
	}
}

void	ft_switch_projection(int key, t_vars *vars)
{
	if (key == I)
		ft_set_isometric(vars);
	if (key == P)
		ft_set_parallel(vars);
	if (key == C)
		ft_set_conic(vars);
}

int	ft_key_hook(int key, t_vars *vars)
{
	if (key == ESCAPE)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_loop_end(vars->mlx);
	}
	if (is_shift_key(key))
		ft_incre_or_decre_shift_var(key, &(vars->shift_x), &(vars->shift_y));
	if (is_switch_projection_key(key))
		ft_switch_projection(key, vars);
	if (key == X)
		vars->roll = 0.523599;
	if (key == Y)
		vars->pitch = 0.523599;
	if (key == Z)
		vars->yaw = 0.523599;
	if (is_valid_key(key) || key == Z || key == X || key == Y)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_clear_window(vars->mlx, vars->win);
		ft_display_map(vars);
		vars->shift_x = 0;
		vars->shift_y = 0;
		vars->yaw = 0.0;
		vars->roll = 0.0;
		vars->pitch = 0.0;
	}
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_vars *vars)
{
	if (is_zoom_up(button, vars->zoom_rate))
		vars->zoom_rate = 2.0;
	if (is_zoom_down(button, vars->zoom_rate))
		vars->zoom_rate = 0.5;
	if ((button == SCROLL_UP && vars->zoom_rate < 100)
		|| (button == SCROLL_DOWN && vars->zoom_rate > 0.0))
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_clear_window(vars->mlx, vars->win);
		vars->mouse_x = (double)x;
		vars->mouse_y = (double)y;
		ft_display_map(vars);
		vars->zoom_rate = 1.0;
		vars->mouse_x = 0;
		vars->mouse_y = 0;
	}
	return (0);
}
