#include "mlx.h"
#include "libft.h"
#include "map_utils.h"
#include <stdio.h>
#include <math.h>

#define ESCAPE 0xff1b
#define WIDTH 750
#define HEIGHT 750
#define OFFSET 0
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

	// cord->xs0 = (cord->x0 - cord->y0) * MESH_LEN * cos(0.8);
	// cord->ys0 = (cord->x0 + cord->y0) * MESH_LEN * sin(0.8);
	// cord->xs1 = (cord->x1 - cord->y1) * MESH_LEN * cos(0.8);
	// cord->ys1 = (cord->x1 + cord->y1) * MESH_LEN * sin(0.8);

	cord->xs0 = cord->x0 * MESH_LEN;
	cord->ys0 = cord->y0 * MESH_LEN;
	cord->xs1 = cord->x1 * MESH_LEN;
	cord->ys1 = cord->y1 * MESH_LEN;
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

t_2dcord	*ft_set_cord(int x0, int y0, int x1, int y1)
{
	t_2dcord	*cord;

	cord = (t_2dcord *)ft_calloc(1, sizeof(t_2dcord));
	cord->x0 = x0;
	cord->y0 = y0;
	cord->x1 = x1;
	cord->y1 = y1;
	return (cord);
}

void	ft_display_map_helper(t_data *img, char ***map)
{
	int	y;
	int	x;
	bool	is_continue;
	t_2dcord	*cord;

	is_continue = true;
	y = 0;
	while (map[y] != NULL)
	{
		
		x = 0;
		while (true)
		{
			if (map[y][x + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x + 1, y);
				ft_draw_line(img, cord);
				free(cord);
			}
			if (map[y + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x, y + 1);
				ft_draw_line(img, cord);
				free(cord);
			}
			if (map[y][x + 1] == NULL)
				break ;
			x++;
		}
		y++;
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
