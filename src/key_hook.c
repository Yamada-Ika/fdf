#include "fdf.h"

static void	_incre_or_decre_shift(int key, int *x, int *y)
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

static void	_switch_projection(int key, t_map_info *vars)
{
	if (key == I)
		ft_set_isometric(vars);
	if (key == P)
		ft_set_parallel(vars);
	if (key == C)
		ft_set_conic(vars);
}

static void	_set_rotation_angle(int key, t_map_info *map)
{
	if (key == X)
	{
		map->yaw = deg_to_radian(0);
		map->roll = deg_to_radian(ROTATION_STEP);
		map->pitch = deg_to_radian(0);
	}
	if (key == Y)
	{
		map->yaw = deg_to_radian(0);
		map->roll = deg_to_radian(0);
		map->pitch = deg_to_radian(ROTATION_STEP);
	}
	if (key == Z)
	{
		map->yaw = deg_to_radian(ROTATION_STEP);
		map->roll = deg_to_radian(0);
		map->pitch = deg_to_radian(0);
	}
}

static void	ft_init_shift_and_angle(t_map_info *map)
{
	map->shift_x = 0;
	map->shift_y = 0;
	map->yaw = deg_to_radian(0);
	map->roll = deg_to_radian(0);
	map->pitch = deg_to_radian(0);
}

int	ft_key_hook(int key, t_map_info *map)
{
	if (key == ESCAPE)
	{
		mlx_destroy_image(map->mlx, map->img.img);
		mlx_destroy_window(map->mlx, map->win);
		mlx_loop_end(map->mlx);
	}
	if (is_shift_key(key))
		_incre_or_decre_shift(key, &(map->shift_x), &(map->shift_y));
	if (is_switch_projection_key(key))
		_switch_projection(key, map);
	if (is_rotation_key(key))
		_set_rotation_angle(key, map);
	if (is_valid_key(key))
	{
		mlx_destroy_image(map->mlx, map->img.img);
		mlx_clear_window(map->mlx, map->win);
		display_map(map);
		ft_init_shift_and_angle(map);
		map->mouse_x = 0.0;
		map->mouse_y = 0.0;
	}
	return (0);
}
