#include "fdf.h"

void	ft_install_hook(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_key_hook, vars);
	mlx_mouse_hook(vars->win, ft_mouse_hook, vars);
}

void	ft_incre_or_decre_shift_var(int key, int *x, int *y)
{
	if (key == RIGHT)
		*x += 5;
	if (key == LEFT)
		*x -= 5;
	if (key == UP)
		*y -= 5;
	if (key == DOWN)
		*y += 5;
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
	if (is_valid_key(key))
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
