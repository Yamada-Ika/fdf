#include "mlx.h"
#include "libft.h"
#include "map_utils.h"
#include <stdio.h>
#include <math.h>

#define ESCAPE 0xff1b
#define WIDTH 750
#define HEIGHT 750
#define OFFSET 10

// mouse
#define SCROLL_UP 4
#define SCROLL_DOWN 5

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

int	g_mesh_len;
int	g_offset;

int	key_hook(int keycode, t_vars *vars)
{
	vars = NULL;
	if (keycode == ESCAPE)
		exit(0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	static unsigned int	zoom = 1;

	vars = NULL;
	// button
	// Up : 4
	// Down : 5
	// x, y : mouse location
	if (button == SCROLL_UP && zoom != 10)
		zoom++;
	if (button == SCROLL_DOWN && zoom != 0)
		zoom--;
	printf("button : %d\n", button);
	printf("x      : %d\n", x);
	printf("y      : %d\n", y);
	printf("zoom   : %u\n", zoom);
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
	// cord->xs0 = cord->x0 * g_mesh_len;
	// cord->ys0 = cord->y0 * g_mesh_len;
	// cord->xs1 = cord->x1 * g_mesh_len;
	// cord->ys1 = cord->y1 * g_mesh_len;

	cord->xs0 = (cos(-0.8) * cord->x0 - sin(-0.8) * cord->y0) * g_mesh_len;
	cord->ys0 = (sin(-0.8) * cord->x0 + cos(-0.8) * cord->y0 - cord->z0) * g_mesh_len * sin(0.52);
	cord->xs1 = (cos(-0.8) * cord->x1 - sin(-0.8) * cord->y1) * g_mesh_len;
	cord->ys1 = (sin(-0.8) * cord->x1 + cos(-0.8) * cord->y1 - cord->z1) * g_mesh_len * sin(0.52);

	// printf("(x0, y0) =   (%d, %d)\n", cord->x0, cord->y0);
	// printf("(xs0, ys0) = (%f, %f)\n", cord->xs0, cord->ys0);
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
	cord->z0 = 0;
	cord->x1 = x1;
	cord->y1 = y1;
	cord->z1 = 0;
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
				cord = ft_set_cord(x, y + g_offset, x + 1, y + g_offset);
				cord->z0 = ft_strtoll(map[y][x] , NULL, 10);
				cord->z1 = ft_strtoll(map[y][x + 1] , NULL, 10);
				ft_draw_line(img, cord);
				free(cord);
			}
			if (map[y + 1] != NULL)
			{
				cord = ft_set_cord(x, y + g_offset, x, y + 1 + g_offset);
				cord->z0 = ft_strtoll(map[y][x] , NULL, 10);
				cord->z1 = ft_strtoll(map[y + 1][x] , NULL, 10);
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

	mlx_clear_window(vars->mlx, vars->win);
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	ft_display_map_helper(&img, map);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

int	ft_get_map_column_count(char ***map)
{
	int	count;

	count = 0;
	while (map[0][count] != NULL)
		count++;
	return (count);
}

int	ft_get_map_raw_count(char ***map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

int	ft_get_map_z_max(char ***map)
{
	int	i;
	int	j;
	int	z_max;

	i = 0;
	z_max = INT_MIN;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != NULL)
		{
			if (z_max < ft_strtoll(map[i][j], NULL, 10))
				z_max = ft_strtoll(map[i][j], NULL, 10);
			j++;
		}
		i++;
	}
	return (z_max);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
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
	g_mesh_len = 10;
	g_offset = 25;
	vars.win = mlx_new_window(vars.mlx, 500, 1000, "fdf");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	ft_display_map(&vars, map);
	mlx_loop(vars.mlx);
}
