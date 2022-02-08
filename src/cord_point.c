#include "fdf.h"

static void	_trans_with_matrix(double **mtx, double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	*x = (mtx[0][0] * prev_x
			+ mtx[0][1] * prev_y
			+ mtx[0][2] * prev_z
			+ mtx[0][3]);
	*y = (mtx[1][0] * prev_x
			+ mtx[1][1] * prev_y
			+ mtx[1][2] * prev_z
			+ mtx[1][3]);
	*z = (mtx[2][0] * prev_x
			+ mtx[2][1] * prev_y
			+ mtx[2][2] * prev_z
			+ mtx[2][3]);
}

void	trans_point(t_point *map0, t_point *map1, double **matrix)
{
	_trans_with_matrix(matrix, &(map0->x), &(map0->y), &(map0->z));
	_trans_with_matrix(matrix, &(map1->x), &(map1->y), &(map1->z));
}
