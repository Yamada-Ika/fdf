#include "fdf.h"

// |x'|   |1 0 0 tx||x|
// |y'| = |0 1 0 ty||y|
// |z'|   |0 0 1 tz||z|
// |1 |   |0 0 0  1||1|
void	set_trans_matrix(double **matrix, double tx, double ty)
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = tx;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = ty;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}

// |x'|   |zr 0  0 0||x|
// |y'| = |0 zr  0 0||y|
// |z'|   |0  0 zr 0||z|
// |0 |   |0  0  0 1||1|
void	set_zoom_matrix(double **matrix, double zoom_rate)
{
	matrix[0][0] = zoom_rate;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = zoom_rate;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = zoom_rate;
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}

// |x'|   |1         0          0 0||x|
// |y'| = |0 cos(roll) -sin(roll) 0||y|
// |z'|   |0 sin(roll)  cos(roll) 0||z|
// |0 |   |0         0         0  1||1|
void	set_rotate_x_matrix(double **matrix, double roll)
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = cos(roll);
	matrix[1][2] = -sin(roll);
	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = sin(roll);
	matrix[2][2] = cos(roll);
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}

// |x'|   | cos(pitch) 0 sin(pitch) 0||x|
// |y'| = |          0 1          0 0||y|
// |z'|   |-sin(pitch) 0 cos(pitch) 0||z|
// |0 |   |          0 0          0 1||1|
void	set_rotate_y_matrix(double **matrix, double pitch)
{
	matrix[0][0] = cos(pitch);
	matrix[0][1] = 0.0;
	matrix[0][2] = sin(pitch);
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = -sin(pitch);
	matrix[2][1] = 0.0;
	matrix[2][2] = cos(pitch);
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}

// |x'|   |cos(yaw) -sin(yaw) 0 0||x|
// |y'| = |sin(yaw)  cos(yaw) 0 0||y|
// |z'|   |       0         0 1 0||z|
// |0 |   |       0         0 0 1||1|
void	set_rotate_z_matrix(double **matrix, double yaw)
{
	matrix[0][0] = cos(yaw);
	matrix[0][1] = -sin(yaw);
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = sin(yaw);
	matrix[1][1] = cos(yaw);
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
