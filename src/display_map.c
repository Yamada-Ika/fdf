#include "fdf.h"

t_2dcord	*ft_set_cord(int x0, int y0, int x1, int y1)
{
	t_2dcord	*cord;

	cord = (t_2dcord *)ft_calloc(1, sizeof(t_2dcord));
	cord->x0 = x0;
	cord->y0 = y0;
	cord->x1 = x1;
	cord->y1 = y1;
	return (cord);
}

void	ft_display_map_helper(t_data *img, t_vars *vars)
{
	int			y;
	int			x;
	t_2dcord	cord;

	// debug_map(vars->map_tmp, vars->map_row_size, vars->map_colmun_size);
	y = 0;
	while (y < vars->map_row_size)
	{
		x = 0;
		while (true)
		{
			if (x + 1 < vars->map_colmun_size)
			{
				cord.x0 = vars->map_tmp[y][x].x;
				cord.y0 = vars->map_tmp[y][x].y;
				cord.z0 = vars->map_tmp[y][x].z;
				vars->color0 = vars->map_tmp[y][x].color;
				cord.x1 = vars->map_tmp[y][x + 1].x;
				cord.y1 = vars->map_tmp[y][x + 1].y;
				cord.z1 = vars->map_tmp[y][x + 1].z;
				vars->color1 = vars->map_tmp[y][x + 1].color;
				// fprintf(stderr, "\n%5f %5f %5f %5f %5f %5f\n", cord.x0, cord.y0, cord.z0, cord.x1, cord.y1, cord.z1);
				ft_draw_line(img, &cord, vars);
				// fprintf(stderr, "%5f %5f %5f %5f %5f %5f\n", cord.x0, cord.y0, cord.z0, cord.x1, cord.y1, cord.z1);
				vars->map_tmp_tmp[y][x].x = cord.x0;
				vars->map_tmp_tmp[y][x].y = cord.y0;
				vars->map_tmp_tmp[y][x].z = cord.z0;
				vars->map_tmp_tmp[y][x + 1].x = cord.x1;
				vars->map_tmp_tmp[y][x + 1].y = cord.y1;
				vars->map_tmp_tmp[y][x + 1].z = cord.z1;
			}
			if (y + 1 < vars->map_row_size)
			{
				cord.x0 = vars->map_tmp[y][x].x;
				cord.y0 = vars->map_tmp[y][x].y;
				cord.z0 = vars->map_tmp[y][x].z;
				vars->color0 = vars->map_tmp[y][x].color;
				cord.x1 = vars->map_tmp[y + 1][x].x;
				cord.y1 = vars->map_tmp[y + 1][x].y;
				cord.z1 = vars->map_tmp[y + 1][x].z;
				vars->color1 = vars->map_tmp[y + 1][x].color;
				// fprintf(stderr, "\n%5f %5f %5f %5f %5f %5f\n", cord.x0, cord.y0, cord.z0, cord.x1, cord.y1, cord.z1);
				ft_draw_line(img, &cord, vars);
				// fprintf(stderr, "%5f %5f %5f %5f %5f %5f\n", cord.x0, cord.y0, cord.z0, cord.x1, cord.y1, cord.z1);
				vars->map_tmp_tmp[y][x].x = cord.x0;
				vars->map_tmp_tmp[y][x].y = cord.y0;
				vars->map_tmp_tmp[y][x].z = cord.z0;
				vars->map_tmp_tmp[y + 1][x].x = cord.x1;
				vars->map_tmp_tmp[y + 1][x].y = cord.y1;
				vars->map_tmp_tmp[y + 1][x].z = cord.z1;
			}
			if (x + 1 == vars->map_colmun_size)
				break ;
			x++;
		}
		y++;
	}
	for (int i = 0; i < vars->map_row_size; i++)
	{
		for (int j = 0; j < vars->map_row_size; j++)
		{
			vars->map_tmp[i][j].x = vars->map_tmp_tmp[i][j].x;
			vars->map_tmp[i][j].y = vars->map_tmp_tmp[i][j].y;
			vars->map_tmp[i][j].z = vars->map_tmp_tmp[i][j].z;
		}
	}
	// fprintf(stderr, "\n");
	// debug_map(vars->map_tmp, vars->map_row_size, vars->map_colmun_size);
}

void	ft_display_map(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_len, &img.endian);
	// ft_set_matrix(vars);
	ft_calc_affine_matrix(vars);
	ft_display_map_helper(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	mlx_string_put(vars->mlx, vars->win, 10, 650, 0xFFFFFF, "shift : arrow key");
	mlx_string_put(vars->mlx, vars->win, 130, 650, 0xFFFFFF, "zoom : track ball");
	mlx_string_put(vars->mlx, vars->win, 250, 650, 0xFFFFFF, "rotate : x y z key");
	mlx_string_put(vars->mlx, vars->win, 380, 650, 0xFFFFFF, "projection : i isometrix p parallel c conic");
	vars->img = img;
}
