#include "fdf.h"

static void	_set_map_origin(t_map_info *map)
{
	map->origin_x = (map->points[map->row_size - 1][map->col_size - 1].x
			- map->points[0][0].x) / 2 + map->points[0][0].x;
	map->origin_y = (map->points[map->row_size - 1][map->col_size - 1].y
			- map->points[0][0].y) / 2 + map->points[0][0].y;
}

static bool	_can_set_image_info(t_image_info *img, t_map_info *map)
{
	img->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (img->img == NULL)
	{
		delete_map(map);
		delete_display(map);
		return (false);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_len, &img->endian);
	map->img = *img;
	return (true);
}

static void	_init_map_meta_info(t_map_info *map)
{
	map->yaw = degree_to_radian(0);
	map->roll = degree_to_radian(0);
	map->pitch = degree_to_radian(0);
	map->zoom_rate = 1.0;
	map->shift_x = 0.0;
	map->shift_y = 0.0;
	map->mouse_x = 0.0;
	map->mouse_y = 0.0;
}

static void	_display_usage(t_map_info *map)
{
	mlx_string_put(map->mlx, map->win, 100, 650, 0xFFFFFF, "shift : arrow key");
	mlx_string_put(map->mlx, map->win, 300, 650, 0xFFFFFF, "zoom : track ball");
	mlx_string_put(map->mlx, map->win, 500, 650, 0xFFFFFF,
		"rotate : x y z key");
}

bool	can_display_map(t_map_info *map)
{
	t_image_info	img;

	if (!_can_set_image_info(&img, map))
		return (false);
	_set_map_origin(map);
	calc_affine_matrix(map);
	put_map_to_image(map);
	mlx_put_image_to_window(map->mlx, map->win, img.img, 0, 0);
	update_map_points(map->points, map->for_update,
		map->row_size, map->col_size);
	_display_usage(map);
	_init_map_meta_info(map);
	return (true);
}
