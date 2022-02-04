#include "fdf.h"

t_map	**ft_create_map(size_t row_size, size_t column_size)
{
	t_map	**map;
	size_t	i;

	map = (t_map **)ft_calloc(row_size, sizeof(t_map *));
	i = 0;
	while (i < row_size)
	{
		map[i] = (t_map *)ft_calloc(column_size, sizeof(t_map));
		i++;
	}
	return (map);
}

void	_set_height_and_color(double *z, int *color, char *val)
{
	char	*color_str;

	color_str = "";
	*z = (double)ft_strtoll(val, &color_str, 10);
	if (color_str[0] == ',')
		*color = ft_strtoll(++color_str, NULL, 16);
	else
		*color = 0xFFFFFF;
}

void	ft_set_map(t_map **map_tmp, char ***map)
{
	int			y;
	int			x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != NULL)
		{
			map_tmp[y][x].x = (double)x;
			map_tmp[y][x].y = (double)y;
			_set_height_and_color(&(map_tmp[y][x].z), &(map_tmp[y][x].color), map[y][x]);
			x++;
		}
		y++;
	}
}

// // gcc create_map.c -I../include -I../minilibx-linux -I../libft -L../libft -lft
// #include <assert.h>

// bool	is_almost_same(double res, double exp)
// {
// 	double	err;

// 	if (exp < 0.01)
// 	{
// 		res += 1.0;
// 		exp += 1.0;
// 	}
// 	err = (res - exp) / exp;
// 	if (err < 0.000000)
// 		err *= -1.0;
// 	if (err < 0.01)
// 		return (true);
// 	else
// 		return (false);
// }

// int main(void)
// {
// 	t_map	**map1;
// 	char	***char_map1;

// 	char_map1 = (char ***)malloc(sizeof(char **) * 4);
// 	char_map1[0] = (char **)malloc(sizeof(char *) * 4);
// 	char_map1[0][0] = ft_strdup("0");
// 	char_map1[0][1] = ft_strdup("3");
// 	char_map1[0][2] = ft_strdup("4");
// 	char_map1[0][3] = NULL;
// 	char_map1[1] = (char **)malloc(sizeof(char *) * 4);
// 	char_map1[1][0] = ft_strdup("2");
// 	char_map1[1][1] = ft_strdup("5");
// 	char_map1[1][2] = ft_strdup("9");
// 	char_map1[1][3] = NULL;
// 	char_map1[2] = (char **)malloc(sizeof(char *) * 4);
// 	char_map1[2][0] = ft_strdup("8,0xff00");
// 	char_map1[2][1] = ft_strdup("7");
// 	char_map1[2][2] = ft_strdup("6");
// 	char_map1[2][3] = NULL;
// 	char_map1[3] = NULL;
// 	map1 = ft_create_map(3, 3);
// 	ft_set_map(map1, char_map1);
// 	assert(is_almost_same(map1[0][0].x, 0.0));
// 	assert(is_almost_same(map1[0][0].y, 0.0));
// 	assert(is_almost_same(map1[0][0].z, 0.0));
// 	assert(map1[0][0].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[0][1].x, 1.0));
// 	assert(is_almost_same(map1[0][1].y, 0.0));
// 	assert(is_almost_same(map1[0][1].z, 3.0));
// 	assert(map1[0][1].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[0][2].x, 2.0));
// 	assert(is_almost_same(map1[0][2].y, 0.0));
// 	assert(is_almost_same(map1[0][2].z, 4.0));
// 	assert(map1[0][2].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[1][0].x, 0.0));
// 	assert(is_almost_same(map1[1][0].y, 1.0));
// 	assert(is_almost_same(map1[1][0].z, 2.0));
// 	assert(map1[1][0].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[1][1].x, 1.0));
// 	assert(is_almost_same(map1[1][1].y, 1.0));
// 	assert(is_almost_same(map1[1][1].z, 5.0));
// 	assert(map1[1][1].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[1][2].x, 2.0));
// 	assert(is_almost_same(map1[1][2].y, 1.0));
// 	assert(is_almost_same(map1[1][2].z, 9.0));
// 	assert(map1[1][2].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[2][0].x, 0.0));
// 	assert(is_almost_same(map1[2][0].y, 2.0));
// 	assert(is_almost_same(map1[2][0].z, 8.0));
// 	assert(map1[2][0].color == 0xff00);
// 	assert(is_almost_same(map1[2][1].x, 1.0));
// 	assert(is_almost_same(map1[2][1].y, 2.0));
// 	assert(is_almost_same(map1[2][1].z, 7.0));
// 	assert(map1[2][1].color == 0xFFFFFF);
// 	assert(is_almost_same(map1[2][2].x, 2.0));
// 	assert(is_almost_same(map1[2][2].y, 2.0));
// 	assert(is_almost_same(map1[2][2].z, 6.0));
// 	assert(map1[2][2].color == 0xFFFFFF);
// }
