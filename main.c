#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>

int	g_x_offset;
int	g_y_offset;

void	ft_display_map(t_vars *vars);
char	***ft_create_map(char *path);

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == RIGHT)
		vars->shift_x += 20;
	if (keycode == LEFT)
		vars->shift_x -= 20;
	if (keycode == UP)
		vars->shift_y -= 20;
	if (keycode == DOWN)
		vars->shift_y += 20;
	if (keycode == RIGHT || keycode == LEFT
		|| keycode == UP || keycode == DOWN)
		ft_display_map(vars);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_vars *vars)
{
	static unsigned int	zoom = 1;

	x = 0;
	y = 0;
	if (button == SCROLL_UP && zoom != 10)
		vars->mesh_len++;
	if (button == SCROLL_DOWN && zoom != 0)
		vars->mesh_len--;
	if ((button == SCROLL_UP && zoom != 10)
		|| (button == SCROLL_DOWN && zoom != 0))
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
	if (cord->y0 < 1.0 || cord->y1 < 1.0 || cord->y0 > HEIGHT - 1.0
		|| cord->y1 > HEIGHT - 1.0 || cord->x0 < 1.0 || cord->x1 < 1.0
		|| cord->x0 > WIDTH - 1.0 || cord->x1 > WIDTH - 1.0)
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
	*y = ((sin(-0.8) * prev_x + cos(-0.8) * prev_y) * sin(0.615472907) - *z) * vars->mesh_len;
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
	int	color_step;

	ft_trans_cord(cord, vars);
	ft_shift_cord(cord, vars);
	if (ft_is_over_img_size(cord))
		return ;
	delta_x = cord->x1 - cord->x0;
	delta_y = cord->y1 - cord->y0;
	step_max = ft_max(delta_x, delta_y);
	delta_x /= step_max;
	delta_y /= step_max;
	// color
	if (vars->color0 == 0)
		vars->color0 = 0xFFFFFF;
	if (vars->color1 == 0)
		vars->color1 = 0xFFFFFF;
	color_step = (vars->color1 - vars->color0) / step_max;
	step = 0;
	while (step < step_max)
	{
		cord->x0 += delta_x;
		cord->y0 += delta_y;
		my_mlx_pixel_put(img, cord->x0, cord->y0, vars->color0);
		vars->color0 += color_step;
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

void	ft_set_z_color_helper1(t_2dcord *cord, t_vars *vars, int y, int x)
{
	char	*color;

	color = "";
	cord->z1 = ft_strtoll(vars->map[y][x], &color, 10);
	if (color[0] == ',')
		vars->color1 = ft_strtoll(++color, NULL, 16);
	else
		vars->color1 = 0;
}

void	ft_set_z_color_helper0(t_2dcord *cord, t_vars *vars, int y, int x)
{
	char	*color;

	color = "";
	cord->z0 = ft_strtoll(vars->map[y][x], &color, 10);
	if (color[0] == ',')
		vars->color0 = ft_strtoll(++color, NULL, 16);
	else
		vars->color0 = 0;
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
				ft_set_z_color_helper0(cord, vars, y, x);
				ft_set_z_color_helper1(cord, vars, y, x + 1);
				ft_draw_line(img, cord, vars);
				free(cord);
			}
			if (vars->map[y + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x, y + 1);
				ft_set_z_color_helper0(cord, vars, y, x);
				ft_set_z_color_helper1(cord, vars, y + 1, x);
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

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
		return (0);
	vars.map = ft_create_map(argv[1]);
	if (vars.map == NULL)
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
	ft_display_map(&vars);
	mlx_loop(vars.mlx);
}
