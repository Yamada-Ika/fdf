#include "mlx.h"
#include "libft.h"
#include "map_utils.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>

int	g_x_offset;
int	g_y_offset;

void	ft_display_map(t_vars *vars);

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		exit(0);
	// left 65361
	// up 65362
	// right 65363
	// down 65364
	if (keycode == RIGHT)
		vars->shift_x += 20;
	if (keycode == LEFT)
		vars->shift_x -= 20;
	if (keycode == UP)
		vars->shift_y -= 20;
	if (keycode == DOWN)
		vars->shift_y += 20;
	ft_display_map(vars);
	printf("keycode : %x\n", keycode);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_vars *vars)
{
	static unsigned int	zoom = 1;

	// vars = NULL;
	// button
	// right : 1
	// Up : 4
	// Down : 5
	// x, y : mouse location
	if (button == SCROLL_UP && zoom != 10)
		vars->mesh_len++;
	if (button == SCROLL_DOWN && zoom != 0)
		vars->mesh_len--;
	printf("button : %d\n", button);
	printf("x      : %d\n", x);
	printf("y      : %d\n", y);
	printf("zoom   : %u\n", zoom);
	ft_display_map(vars);
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

bool	ft_is_over_img_size(t_2dcord *cord)
{
	if (cord->y0 < 0.0 || cord->y1 < 0.0 || cord->y0 > HEIGHT
		|| cord->y1 > HEIGHT || cord->x0 < 0.0 || cord->x1 < 0.0
		|| cord->x0 > WIDTH || cord->x1 > WIDTH)
		return (true);
	return (false);
}

void	ft_trans_isometric(t_vars *vars, double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (cos(-0.8) * prev_x - sin(-0.8) * prev_y) * vars->mesh_len;
	*y = (sin(-0.8) * prev_x + cos(-0.8) * prev_y - *z) * vars->mesh_len;
}

void	ft_trans_cord(t_2dcord *cord, t_vars *vars)
{
	ft_trans_isometric(vars, &(cord->x0), &(cord->y0), &(cord->z0));
	ft_trans_isometric(vars, &(cord->x1), &(cord->y1), &(cord->z1));
}

void	ft_shift_cord(t_2dcord *cord, t_vars *vars)
{
	cord->x0 += vars->shift_x;
	cord->x1 += vars->shift_x;
	cord->y0 += vars->shift_y;
	cord->y1 += vars->shift_y;
}

void	ft_draw_line(t_data *img, t_2dcord *cord, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	int	step;
	double	step_max;

	ft_trans_cord(cord, vars);
	ft_shift_cord(cord, vars);
	if (ft_is_over_img_size(cord))
		return ;
	delta_x = cord->x1 - cord->x0;
	delta_y = cord->y1 - cord->y0;
	step_max = ft_max(delta_x, delta_y);
	delta_x /= step_max;
	delta_y /= step_max;
	step = 0;
	while (step < step_max)
	{
		cord->x0 += delta_x;
		cord->y0 += delta_y;
		my_mlx_pixel_put(img, cord->x0, cord->y0, 0xFFFFFF);
		step++;
	}
}

t_2dcord	*ft_set_cord(int x0, int y0, int x1, int y1)
{
	t_2dcord	*cord;

	cord = (t_2dcord *)ft_calloc(1, sizeof(t_2dcord));
	cord->x0 = x0 + g_x_offset;
	cord->y0 = y0 + g_y_offset;
	cord->z0 = 0;
	cord->x1 = x1 + g_x_offset;
	cord->y1 = y1 + g_y_offset;
	cord->z1 = 0;
	return (cord);
}

void	ft_display_map_helper(t_data *img, t_vars *vars)
{
	int	y;
	int	x;
	bool	is_continue;
	t_2dcord	*cord;

	is_continue = true;
	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (true)
		{
			if (vars->map[y][x + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x + 1, y);
				cord->z0 = ft_strtoll(vars->map[y][x] , NULL, 10);
				cord->z1 = ft_strtoll(vars->map[y][x + 1] , NULL, 10);
				ft_draw_line(img, cord, vars);
				free(cord);
			}
			if (vars->map[y + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x, y + 1);
				cord->z0 = ft_strtoll(vars->map[y][x] , NULL, 10);
				cord->z1 = ft_strtoll(vars->map[y + 1][x] , NULL, 10);
				ft_draw_line(img, cord, vars);
				free(cord);
			}
			if (vars->map[y][x + 1] == NULL)
				break ;
			x++;
		}
		y++;
	}
}

void	ft_display_map(t_vars *vars)
{
	t_data	img;

	mlx_clear_window(vars->mlx, vars->win);
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	ft_display_map_helper(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
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
	vars.mesh_len = 1;
	g_x_offset = 0;
	g_y_offset = 100;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	mlx_key_hook(vars.win, ft_key_hook, &vars);
	mlx_mouse_hook(vars.win, ft_mouse_hook, &vars);
	vars.map = map;
	ft_display_map(&vars);
	mlx_loop(vars.mlx);
}
