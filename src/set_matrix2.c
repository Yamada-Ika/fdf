#include "fdf.h"

// |x'|   |1 0 0 0||x|
// |y'| = |0 1 0 0||y|
// |0 |   |0 0 1 0||z|
// |0 |   |0 0 0 1||1|
void	set_unit_matrix(double **matrix)
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}
