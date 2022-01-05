#include "mlx.h"
#include "libft.h"
#include "map_utils.h"
#include <stdio.h>
#include <math.h>

#define ESCAPE 0xff1b
#define WIDTH 750
#define HEIGHT 750
#define OFFSET 10
#define MESH_LEN 20

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_data;

typedef struct	s_2dcord
{
	int	x0;
	int	y0;
	int	z0;
	int	x1;
	int	y1;
	int	z1;
	double	xs0;
	double	ys0;
	double	xs1;
	double	ys1;
}	t_2dcord;


int	key_hook(int keycode, t_vars *vars)
{
	vars = NULL;
	if (keycode == ESCAPE)
		exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	ft_max(double n1, double n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

void	ft_trans_cord(t_2dcord *cord)
{
	// cord->xs0 = (cos(-0.8) * cord->x0 - sin(-0.8) * cord->y0) * MESH_LEN;
	// cord->ys0 = (sin(-0.8) * cord->x0 + cos(-0.8) * cord->y0 - cord->z0) * MESH_LEN * sin(0.52);
	// cord->xs1 = (cos(-0.8) * cord->x1 - sin(-0.8) * cord->y1) * MESH_LEN;
	// cord->ys1 = (sin(-0.8) * cord->x1 + cos(-0.8) * cord->y1 - cord->z1) * MESH_LEN * sin(0.52);

	cord->xs0 = (cord->x0 - cord->y0) * MESH_LEN * cos(0.8);
	cord->ys0 = (cord->x0 + cord->y0) * MESH_LEN * sin(0.8);
	cord->xs1 = (cord->x1 - cord->y1) * MESH_LEN * cos(0.8);
	cord->ys1 = (cord->x1 + cord->y1) * MESH_LEN * sin(0.8);
	printf("(x0, y0) =   (%d, %d)\n", cord->x0, cord->y0);
	printf("(xs0, ys0) = (%f, %f)\n", cord->xs0, cord->ys0);
}

void	ft_draw_line(t_data *img, t_2dcord *cord)
{
	double	delta_x;
	double	delta_y;
	int	step;
	double	step_max;

	ft_trans_cord(cord);
	delta_x = cord->xs1 - cord->xs0;
	delta_y = cord->ys1 - cord->ys0;
	step_max = ft_max(delta_x, delta_y);
	delta_x /= step_max;
	delta_y /= step_max;
	step = 0;
	while (step < step_max)
	{
		cord->xs0 += delta_x;
		cord->ys0 += delta_y;
		my_mlx_pixel_put(img, cord->xs0, cord->ys0, 0xFFFFFF);
		step++;
	}
}

void	ft_display_map_helper(t_data *img, char ***map)
{
	int	i;
	int	j;
	t_2dcord	cord;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i + 1] == NULL)
			break ;
		j = 0;
		while (map[i][j] != NULL)
		{
			cord.x0 = j + OFFSET;
			cord.y0 = i;
			cord.z0 = ft_strtoll(map[i][j], NULL, 10);
			cord.x1 = cord.x0 + 1;
			cord.y1 = cord.y0;
			if (map[i][j + 1] != NULL)
				cord.z1 = ft_strtoll(map[i][j + 1], NULL, 10);
			else
				cord.z1 = 0;
			if (map[i][j + 1] != NULL)
				ft_draw_line(img, &cord);
			cord.x1 = cord.x0;
			cord.y1 = cord.y0 + 1;
			if (map[i + 1][j] != NULL)
				cord.z1 = ft_strtoll(map[i + 1][j], NULL, 10);
			else
				cord.z1 = 0;
			if (j != 0)
				ft_draw_line(img, &cord);
			j++;
		}
		i++;
	}
}

void	ft_display_map(t_vars *vars, char ***map)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	ft_display_map_helper(&img, map);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

int	ft_get_map_width(char ***map)
{
	int	width;

	width = 0;
	while (map[0][width] != NULL)
		width++;
	return (width * 100);
}

int	ft_get_map_height(char ***map)
{
	int	height;

	height = 0;
	while (map[height] != NULL)
		height++;
	return (height * 100);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	char	*fdf;
	char	***map;

	if (argc != 2)
		return (0);
	fdf = ft_read_fdf(argv[1]);
	if (fdf == NULL)
		return (0);
	map = ft_create_map(fdf);
	if (map == NULL)
		return (0);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (0);
	vars.win = mlx_new_window(vars.mlx, ft_get_map_width(map), ft_get_map_height(map), "fdf");
	mlx_key_hook(vars.win, key_hook, &vars);
	ft_display_map(&vars, map);
	mlx_loop(vars.mlx);
}
