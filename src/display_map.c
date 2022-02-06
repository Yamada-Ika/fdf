#include "fdf.h"

static void	_update_map(t_map **dst, t_map **src, size_t row_size, size_t column_size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < row_size)
	{
		j = 0;
		while (j < column_size)
		{
			dst[i][j].x = src[i][j].x;
			dst[i][j].y = src[i][j].y;
			dst[i][j].z = src[i][j].z;
			j++;
		}
		i++;
	}
}

void	ft_display_map_helper(t_data *img, t_vars *vars)
{
	int		y;
	int		x;
	t_map	map0;
	t_map	map1;

	y = 0;
	while (y < vars->map_row_size)
	{
		x = 0;
		while (true)
		{
			if (x + 1 < vars->map_column_size)
			{
				map0.x = vars->map[y][x].x;
				map0.y = vars->map[y][x].y;
				map0.z = vars->map[y][x].z;
				map0.color = vars->map[y][x].color;
				map1.x = vars->map[y][x + 1].x;
				map1.y = vars->map[y][x + 1].y;
				map1.z = vars->map[y][x + 1].z;
				map1.color = vars->map[y][x + 1].color;
				ft_draw_line(img, &map0, &map1, vars->affine_matrix);
				vars->map_tmp[y][x].x = map0.x;
				vars->map_tmp[y][x].y = map0.y;
				vars->map_tmp[y][x].z = map0.z;
				vars->map_tmp[y][x].color = map0.color;
				vars->map_tmp[y][x + 1].x = map1.x;
				vars->map_tmp[y][x + 1].y = map1.y;
				vars->map_tmp[y][x + 1].z = map1.z;
				vars->map_tmp[y][x + 1].color = map1.color;
			}
			if (y + 1 < vars->map_row_size)
			{
				map0.x = vars->map[y][x].x;
				map0.y = vars->map[y][x].y;
				map0.z = vars->map[y][x].z;
				map0.color = vars->map[y][x].color;
				map1.x = vars->map[y + 1][x].x;
				map1.y = vars->map[y + 1][x].y;
				map1.z = vars->map[y + 1][x].z;
				map1.color = vars->map[y + 1][x].color;
				ft_draw_line(img, &map0, &map1, vars->affine_matrix);
				vars->map_tmp[y][x].x = map0.x;
				vars->map_tmp[y][x].y = map0.y;
				vars->map_tmp[y][x].z = map0.z;
				vars->map_tmp[y][x].color = map0.color;
				vars->map_tmp[y + 1][x].x = map1.x;
				vars->map_tmp[y + 1][x].y = map1.y;
				vars->map_tmp[y + 1][x].z = map1.z;
				vars->map_tmp[y + 1][x].color = map1.color;
			}
			if (x + 1 == vars->map_column_size)
				break ;
			x++;
		}
		y++;
	}
	_update_map(vars->map, vars->map_tmp, vars->map_row_size, vars->map_column_size);
	// debug_map(vars->map, vars->map_row_size, vars->map_column_size);
}

void	ft_display_map(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_len, &img.endian);
	ft_calc_affine_matrix(vars);
	ft_display_map_helper(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 10, 650, 0xFFFFFF, "shift : arrow key");
	mlx_string_put(vars->mlx, vars->win, 130, 650, 0xFFFFFF, "zoom : track ball");
	mlx_string_put(vars->mlx, vars->win, 250, 650, 0xFFFFFF, "rotate : x y z key");
	mlx_string_put(vars->mlx, vars->win, 380, 650, 0xFFFFFF, "projection : i isometrix p parallel c conic");
	vars->img = img;
}
