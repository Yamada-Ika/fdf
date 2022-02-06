#include "fdf.h"

void	_debug_matrix(double **matrix)
{
	fprintf(stderr, "%5f %5f %5f %5f\n", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
	fprintf(stderr, "%5f %5f %5f %5f\n", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
	fprintf(stderr, "%5f %5f %5f %5f\n", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
	fprintf(stderr, "%5f %5f %5f %5f\n\n", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
}

void	debug_xy(double x, double y)
{
	fprintf(stderr, "(x, y) = (%5f. %5f)\n", x, y);
}

void	debug_cord(t_2dcord *cord)
{
	fprintf(stderr, "x_0 = (%5f, %5f, %5f) x_1 = (%5f, %5f, %5f)\n", cord->x0, cord->y0, cord->z0, cord->x1, cord->y1, cord->z1);
}

void	debug_map(t_map **map, size_t row_size, size_t col_size)
{
	size_t	y;
	size_t	x;

	fprintf(stderr, "row_size : %zu col_size : %zu\n", row_size, col_size);
	y = 0;
	while (y < row_size)
	{
		x = 0;
		while (x < col_size)
		{
			fprintf(stderr, "(%5f, %5f, %5f)\n", map[y][x].x, map[y][x].y, map[y][x].z);
			x++;
		}
		y++;
	}
}

// void	_debug_print_vars(t_vars *vars)
// {
// 	fprintf(stderr, "center of map index : (%5d, %5d)\n", vars->center_colm, vars->center_row);
// 	fprintf(stderr, "center of map       : (%5f, %5f)\n", vars->origin_x, vars->origin_y);
// 	fprintf(stderr, "mouse at            : (%5f, %5f)\n", vars->zoom_center_x, vars->zoom_center_y);
// }

// void	debug_prev_cords(t_cord_pair **cords, int row_size, int column_size)
// {
// 	// int	i;
// 	// int	j;

// 	// // fprintf(stderr, "%p\n", cords[0]);
// 	// // fprintf(stderr, "%p\n", cords[1]);
// 	// i = 0;
// 	// while (i < row_size)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < column_size)
// 	// 	{
// 	// 		fprintf(stderr, "(x, y) = (%5f, %5f)\n", cords[i][j].x, cords[i][j].y);
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// 	fprintf(stderr, "debug_prev_cords\n");
// 	fprintf(stderr, "(x, y) = (%5f, %5f)\n", cords[0][0].x, cords[0][0].y);
// 	fprintf(stderr, "(x, y) = (%5f, %5f)\n", cords[0][column_size-1].x, cords[0][column_size-1].y);
// 	fprintf(stderr, "(x, y) = (%5f, %5f)\n", cords[row_size-1][0].x, cords[row_size-1][0].y);
// 	fprintf(stderr, "(x, y) = (%5f, %5f)\n", cords[row_size-1][column_size-1].x, cords[row_size-1][column_size-1].y);
// }

// void	_debug_put_zoom_center(t_data *img, t_vars *vars)
// {
// 	for (int y = (int)vars->zoom_center_y - 3; y < vars->zoom_center_y + 3; y++)
// 	{
// 		for (int x = (int)vars->zoom_center_x - 3; x < vars->zoom_center_x + 3; x++)
// 		{
// 			if (x < 0 || y < 0)
// 				break ;
// 			my_mlx_pixel_put(img, x, y, 0x00AE95);
// 		}
// 	}
// }

void	_debug_put_origin(t_data *img, double center_x, double center_y)
{
	fprintf(stderr, "center_x %5f center_y %5f\n", center_x, center_y);
	for (int y = (int)center_y - 3; y < (int)center_y + 3; y++)
	{
		for (int x = (int)center_x - 3; x < (int)center_x + 3; x++)
		{
			my_mlx_pixel_put(img, x, y, 0xF15B5B);
		}
	}
}

