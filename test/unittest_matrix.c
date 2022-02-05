#include "unittest.h"

static	bool	_is_almost_same(double n1, double n2)
{
	double	rel_err;

	if (n1 < 0.01)
		n1 += 1.0;
	if (n2 < 0.01)
		n2 += 1.0;
	rel_err = (n1 - n2) / n2;
	if (rel_err < 0.01)
		return (true);
	else
		return (false);
}

void	_TESTproduct_matrix(void)
{
	double	**matrix1;
	double	**matrix2;

	matrix1 = _create_matrix();
	matrix2 = _create_matrix();

	/*
		|1 0 0 0| |1 0 0 0|
		|0 1 0 0| |0 1 0 0|
		|0 0 1 0| |0 0 1 0|
		|0 0 0 1| |0 0 0 1|
	*/
	matrix1[0][0] = 1.0;
	matrix1[1][1] = 1.0;
	matrix1[2][2] = 1.0;
	matrix1[3][3] = 1.0;
	matrix2[0][0] = 1.0;
	matrix2[1][1] = 1.0;
	matrix2[2][2] = 1.0;
	matrix2[3][3] = 1.0;
	product_matrix(matrix1, matrix2);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// fprintf(stderr, "%d %d %f\n", i, j, matrix1[i][j]);
			if (i == j)
				assert(_is_almost_same(matrix1[i][j], 1.0));
			else
			{
				// fprintf(stderr, "%d %d %f\n", i, j, matrix1[i][j]);
				assert(_is_almost_same(matrix1[i][j], 0.0));
			}
		}
	}

	/*
		|1 1 1 1| |1 0 1 1|
		|1 1 1 1| |1 1 1 1|
		|1 1 1 1| |1 1 1 1|
		|1 1 1 1| |1 1 1 1|
	*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix1[i][j] = 1.0;
			matrix2[i][j] = 1.0;
		}
	}
	product_matrix(matrix1, matrix2);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// fprintf(stderr, "%d %d %f\n", i, j, matrix1[i][j]);
			assert(_is_almost_same(matrix1[i][j], 4.0));
		}
	}

	matrix1[0][0] = 1.0;
	matrix1[0][1] = 3.0;
	matrix1[0][2] = 0.0;
	matrix1[0][3] = 3.0;
	matrix1[1][0] = 0.0;
	matrix1[1][1] = 7.0;
	matrix1[1][2] = 4.0;
	matrix1[1][3] = 4.0;
	matrix1[2][0] = 2.0;
	matrix1[2][1] = 6.0;
	matrix1[2][2] = 3.0;
	matrix1[2][3] = 2.0;
	matrix1[3][0] = 0.0;
	matrix1[3][1] = 10.0;
	matrix1[3][2] = 2.0;
	matrix1[3][3] = 0.0;
	matrix2[0][0] = 0.0;
	matrix2[0][1] = 7.0;
	matrix2[0][2] = 7.0;
	matrix2[0][3] = 0.0;
	matrix2[1][0] = 3.0;
	matrix2[1][1] = 1.0;
	matrix2[1][2] = 6.0;
	matrix2[1][3] = 0.0;
	matrix2[2][0] = 3.0;
	matrix2[2][1] = 2.0;
	matrix2[2][2] = 1.0;
	matrix2[2][3] = 5.0;
	matrix2[3][0] = 2.0;
	matrix2[3][1] = 0.0;
	matrix2[3][2] = 4.0;
	matrix2[3][3] = 1.0;
	product_matrix(matrix1, matrix2);
	// for (int i = 0; i < 4; i++)
	// {
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		// fprintf(stderr, "%d %d %f\n", i, j, matrix1[i][j]);
	// 		// assert(_is_almost_same(matrix1[i][j], 4.0));
	// 	}
	// }
	assert(_is_almost_same(matrix1[0][0], 15.0));
	assert(_is_almost_same(matrix1[0][1], 10.0));
	assert(_is_almost_same(matrix1[0][2], 37.0));
	assert(_is_almost_same(matrix1[0][3], 3.0));
	assert(_is_almost_same(matrix1[1][0], 41.0));
	assert(_is_almost_same(matrix1[1][1], 15.0));
	assert(_is_almost_same(matrix1[1][2], 62.0));
	assert(_is_almost_same(matrix1[1][3], 24.0));
	assert(_is_almost_same(matrix1[2][0], 31.0));
	assert(_is_almost_same(matrix1[2][1], 26.0));
	assert(_is_almost_same(matrix1[2][2], 61.0));
	assert(_is_almost_same(matrix1[2][3], 17.0));
	assert(_is_almost_same(matrix1[3][0], 36.0));
	assert(_is_almost_same(matrix1[3][1], 14.0));
	assert(_is_almost_same(matrix1[3][2], 62.0));
	assert(_is_almost_same(matrix1[3][3], 10.0));


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				matrix1[i][j] = 1.0;
				matrix2[i][j] = 5.0;
			}
			else
			{
				matrix1[i][j] = 0.0;
				matrix2[i][j] = 0.0;
			}
		}
	}
	matrix1[0][3] = 10.0;
	matrix1[1][3] = 10.0;
	product_matrix(matrix1, matrix2);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0 && j == 3 || i == 1 && j == 3)
				assert(_is_almost_same(matrix1[i][j], 50.0));
			else if (i == j)
				assert(_is_almost_same(matrix1[i][j], 5.0));
			else
				assert(_is_almost_same(matrix1[i][j], 0.0));
		}
	}
}

// compile : gcc unittest_matrix.c ../src/affine_matrix.c  -I../libft -I../include -I../minilibx-linux -L../libft -lft
int	main(void)
{
	_TESTproduct_matrix();
}
