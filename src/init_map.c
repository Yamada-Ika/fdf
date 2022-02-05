#include "fdf.h"

void	_set_z_and_color(double *z, int *color, char *val)
{
	char	*color_str;

	color_str = "";
	*z = (double)ft_strtoll(val, &color_str, 10);
	if (color_str[0] == ',')
		*color = ft_strtoll(++color_str, NULL, 16);
	else
		*color = 0xFFFFFF;
}

void	ft_init_map(t_map **map, char ***str_map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str_map[i] != NULL)
	{
		j = 0;
		while (str_map[i][j] != NULL)
		{
			map[i][j].x = (double)j;
			map[i][j].y = (double)i;
			_set_z_and_color(&(map[i][j].z), &(map[i][j].color), str_map[i][j]);
			j++;
		}
		i++;
	}
}
