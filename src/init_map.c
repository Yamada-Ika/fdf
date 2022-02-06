#include "fdf.h"

static void	_init_z_val_and_color(double *z, unsigned int *color, char *val)
{
	char	*color_str;

	color_str = "";
	*z = (double)ft_strtoll(val, &color_str, 10);
	if (color_str[0] == ',')
		*color = ft_strtoll(++color_str, NULL, 16);
	else
		*color = 0xFFFFFF;
}

void	ft_init_point(t_point **points, char ***str_map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str_map[i] != NULL)
	{
		j = 0;
		while (str_map[i][j] != NULL)
		{
			points[i][j].x = (double)j;
			points[i][j].y = (double)i;
			_init_z_val_and_color(&(points[i][j].z),
				&(points[i][j].color), str_map[i][j]);
			j++;
		}
		i++;
	}
}
