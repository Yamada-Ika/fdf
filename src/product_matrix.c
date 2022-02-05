#include "fdf.h"

static void	_copy_matrix(double **dst, double **src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	product_matrix(double **matrix1, double **matrix2, double **tmp_matrix)
{
	double	_prod_v;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			_prod_v = 0.0;
			k = 0;
			while (k < 4)
			{
				_prod_v += matrix1[i][k] * matrix2[k][j];
				k++;
			}
			tmp_matrix[i][j] = _prod_v;
			j++;
		}
		i++;
	}
	_copy_matrix(matrix1, tmp_matrix);
}
