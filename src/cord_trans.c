#include "fdf.h"

void	ft_rotation(double **matrix, double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	*x = (matrix[0][0] * prev_x
			+ matrix[0][1] * prev_y
			+ matrix[0][2] * prev_z
			+ matrix[0][3]);
	*y = (matrix[1][0] * prev_x
			+ matrix[1][1] * prev_y
			+ matrix[1][2] * prev_z
			+ matrix[1][3]);
}

void	ft_trans_cord(t_map *map0, t_map *map1, double **matrix)
{
	ft_rotation(matrix, &(map0->x), &(map0->y), &(map0->z));
	ft_rotation(matrix, &(map1->x), &(map1->y), &(map1->z));
}
