#include "fdf.h"

static void	_set_map_origin(t_map_info *map)
{
	map->origin_x = (map->points[map->row_size - 1][map->col_size - 1].x
			- map->points[0][0].x) / 2 + map->points[0][0].x;
	map->origin_y = (map->points[map->row_size - 1][map->col_size - 1].y
			- map->points[0][0].y) / 2 + map->points[0][0].y;
}

static void	_set_image_info(t_image_info *img, t_map_info *map)
{
	img->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_len, &img->endian);
}

void	display_map(t_map_info *map)
{
	t_image_info	img;

	_set_image_info(&img, map);
	map->img = img;
	_set_map_origin(map);
	ft_calc_affine_matrix(map);
	ft_put_map_to_image(&img, map);
	update_map_points(map->points, map->for_update,
		map->row_size, map->col_size);
	mlx_put_image_to_window(map->mlx, map->win, img.img, 0, 0);
	mlx_string_put(map->mlx, map->win, 10, 650, 0xFFFFFF, "shift : arrow key");
	mlx_string_put(map->mlx, map->win, 130, 650, 0xFFFFFF, "zoom : track ball");
	mlx_string_put(map->mlx, map->win, 250, 650, 0xFFFFFF,
		"rotate : x y z key");
	mlx_string_put(map->mlx, map->win, 380, 650, 0xFFFFFF,
		"projection : i isometrix p parallel c conic");
}
