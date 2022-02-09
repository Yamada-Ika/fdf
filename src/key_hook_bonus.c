#include "fdf.h"

static void	_incre_or_decre_shift(int key, double *x, double *y)
{
	if (key == RIGHT)
	{
		*x = TRANS_STEP;
		*y = 0.0;
	}
	if (key == LEFT)
	{
		*x = -TRANS_STEP;
		*y = 0.0;
	}
	if (key == UP)
	{
		*x = 0.0;
		*y = -TRANS_STEP;
	}
	if (key == DOWN)
	{
		*x = 0.0;
		*y = TRANS_STEP;
	}
}

static void	_set_rotation_angle(int key, t_map_info *map)
{
	if (key == X)
	{
		map->yaw = degree_to_radian(0);
		map->roll = degree_to_radian(ROTATION_STEP);
		map->pitch = degree_to_radian(0);
	}
	if (key == Y)
	{
		map->yaw = degree_to_radian(0);
		map->roll = degree_to_radian(0);
		map->pitch = degree_to_radian(ROTATION_STEP);
	}
	if (key == Z)
	{
		map->yaw = degree_to_radian(ROTATION_STEP);
		map->roll = degree_to_radian(0);
		map->pitch = degree_to_radian(0);
	}
}

int	key_hook(int key, t_map_info *map)
{
	if (key == ESCAPE)
		mlx_loop_end(map->mlx);
	if (is_shift_key(key))
		_incre_or_decre_shift(key, &(map->shift_x), &(map->shift_y));
	if (is_rotation_key(key))
		_set_rotation_angle(key, map);
	if (is_valid_key(key))
	{
		if (!can_redisplay_map(map))
			mlx_loop_end(map->mlx);
	}
	return (0);
}
