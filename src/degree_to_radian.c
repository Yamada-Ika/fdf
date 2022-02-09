#include "fdf.h"

double	degree_to_radian(int deg)
{
	double	radian;

	radian = M_PI / 180 * (double)deg;
	return (radian);
}
