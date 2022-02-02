#include "fdf.h"

double	ft_max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

double	ft_abs(double n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
