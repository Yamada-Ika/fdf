#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>

int	g_x_offset;
int	g_y_offset;

void	ft_display_map(t_vars *vars);
char	***ft_create_map(char *path);

// ft_set_projection.c
void	ft_set_isometric(t_vars *vars);
void	ft_set_parallel(t_vars *vars);
void	ft_set_conic(t_vars *vars);

void	ft_create_affine_matrix(t_vars *vars)
{
	vars->affine_matrix = (double **)ft_calloc(4, sizeof(double *));
	vars->affine_matrix[0] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[1] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[2] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[3] = (double *)ft_calloc(4, sizeof(double));
}

// |x'|   |cos(z_angle) -sin(z_angle)  0 Tx||x|
// |y'| = |sin(z_angle) cos(z_angle)  -1 Ty||y|
// |0 |   |0            0              0  0||z|
// |0 |   |0            0              0  0||1|
void	ft_set_affine_matrix(t_vars *vars)
{
	vars->affine_matrix[0][0] = cos(vars->z_angle) * vars->zoom_rate;
	vars->affine_matrix[0][1] = -sin(vars->z_angle) * vars->zoom_rate;
	vars->affine_matrix[0][3] = vars->shift_x * vars->zoom_rate;
	vars->affine_matrix[1][0] = sin(vars->z_angle) * sin(vars->x_angle) * vars->zoom_rate;
	vars->affine_matrix[1][1] = cos(vars->z_angle) * sin(vars->x_angle) * vars->zoom_rate;
	vars->affine_matrix[1][2] = -1.0 * vars->zoom_rate;
	vars->affine_matrix[1][3] = vars->shift_y * vars->zoom_rate;
}

void	ft_set_mouse_center(t_vars *vars, int x, int y)
{
	vars->shift_x = x;
	vars->shift_y = y;
}

int	ft_key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		exit(0);
	if (keycode == RIGHT)
		vars->shift_x += 5;
	if (keycode == LEFT)
		vars->shift_x -= 5;
	if (keycode == UP)
		vars->shift_y -= 5;
	if (keycode == DOWN)
		vars->shift_y += 5;
	if (keycode == I)
		ft_set_isometric(vars);
	if (keycode == P)
		ft_set_parallel(vars);
	if (keycode == C)
		ft_set_conic(vars);
	if (keycode == RIGHT || keycode == LEFT
		|| keycode == UP || keycode == DOWN
		|| keycode == I || keycode == P
		|| keycode == C)
		{
			ft_display_map(vars);
		}
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_vars *vars)
{
	x = y;
	if (button == SCROLL_UP && vars->zoom_rate < 100)
		vars->zoom_rate += 0.1;
	if (button == SCROLL_DOWN && vars->zoom_rate > 0.1)
		vars->zoom_rate -= 0.1;
	if ((button == SCROLL_UP&& vars->zoom_rate < 100)
		|| (button == SCROLL_DOWN && vars->zoom_rate > 0.0))
		{
			// x = y;
			// ft_set_mouse_center(vars, x, y);
			// printf("shift_x %d shift_y %d\n", vars->shift_x, vars->shift_y);
			ft_display_map(vars);
		}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool	ft_is_over_img_size(t_2dcord *cord)
{
	if (cord->y0 < 1.0 || cord->y1 < 1.0 || cord->y0 > HEIGHT - 1.0
		|| cord->y1 > HEIGHT - 1.0 || cord->x0 < 1.0 || cord->x1 < 1.0
		|| cord->x0 > WIDTH - 1.0 || cord->x1 > WIDTH - 1.0)
		return (true);
	return (false);
}

void	ft_rotation(t_vars *vars, double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	*x = (vars->affine_matrix[0][0] * prev_x + vars->affine_matrix[0][1]
		* prev_y + vars->affine_matrix[0][2] * prev_z + vars->affine_matrix[0][3]) * vars->mesh_len;
	*y = (vars->affine_matrix[1][0] * prev_x + vars->affine_matrix[1][1]
		* prev_y + vars->affine_matrix[1][2] * prev_z + vars->affine_matrix[1][3]) * vars->mesh_len;
}

void	ft_trans_cord(t_2dcord *cord, t_vars *vars)
{
	ft_rotation(vars, &(cord->x0), &(cord->y0), &(cord->z0));
	ft_rotation(vars, &(cord->x1), &(cord->y1), &(cord->z1));
}

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

void	ft_draw_line(t_data *img, t_2dcord *cord, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	int	step;
	double	step_max;
	int	color_step;

	ft_trans_cord(cord, vars);
	if (ft_is_over_img_size(cord))
		return ;
	delta_x = cord->x1 - cord->x0;
	delta_y = cord->y1 - cord->y0;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
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
	cord->x1 = x1 + g_x_offset;
	cord->y1 = y1 + g_y_offset;
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
	t_2dcord	*cord;

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
	ft_set_affine_matrix(vars);
	ft_display_map_helper(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}

void	ft_init_vars(t_vars *vars)
{
	vars->mesh_len = 10;
	vars->x_angle = 0.615;
	vars->z_angle = -0.8;
	vars->zoom_rate = 1.0;
	vars->shift_x = 10;
	vars->shift_y = 10;
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
	ft_create_affine_matrix(&vars);
	ft_init_vars(&vars);
	g_x_offset = 0;
	g_y_offset = 100;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	mlx_key_hook(vars.win, ft_key_hook, &vars);
	mlx_mouse_hook(vars.win, ft_mouse_hook, &vars);
	ft_display_map(&vars);
	mlx_loop(vars.mlx);
}
