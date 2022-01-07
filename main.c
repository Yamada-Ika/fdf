#include "mlx.h"
#include "libft.h"
#include "map_utils.h"
#include <stdio.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 1000
#define OFFSET 10

// mouse
#define R_CLICK 1
#define SCROLL_UP 4
#define SCROLL_DOWN 5

// key
#define ESCAPE 0xff1b
#define LEFT 0xff51
#define UP 0xff52
#define RIGHT 0xff53
#define DOWN 0xff54

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	***map;
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
int	g_x_offset;
int	g_y_offset;
int	g_shift_x;
int	g_shift_y;

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
		g_shift_x += 10;
	if (keycode == LEFT)
		g_shift_x -= 10;
	if (keycode == UP)
		g_shift_y -= 10;
	if (keycode == DOWN)
		g_shift_y += 10;
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
		g_mesh_len++;
	if (button == SCROLL_DOWN && zoom != 0)
		g_mesh_len--;
	printf("button : %d\n", button);
	printf("x      : %d\n", x);
	printf("y      : %d\n", y);
	printf("zoom   : %u\n", zoom);
	ft_display_map(vars);
	return (0);
}

int	ft_move_hook(int button, int x, int y, t_vars *vars)
{
	button = 0;
	x = y;
	vars = NULL;
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
	if (cord->ys0 < 0.0 || cord->ys1 < 0.0 ||cord->ys0 > HEIGHT
		|| cord->ys1 > HEIGHT || cord->xs0 < 0.0 || cord->xs1 < 0.0
		|| cord->xs0 > WIDTH || cord->xs1 > WIDTH)
		return (true);
	return (false);
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
}

void	ft_draw_line(t_data *img, t_2dcord *cord)
{
	double	delta_x;
	double	delta_y;
	int	step;
	double	step_max;

	ft_trans_cord(cord);
	cord->xs0 += g_shift_x;
	cord->xs1 += g_shift_x;
	cord->ys0 += g_shift_y;
	cord->ys1 += g_shift_y;
	if (ft_is_over_img_size(cord))
		return ;
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
	cord->x0 = x0 + g_x_offset;
	cord->y0 = y0 + g_y_offset;
	cord->z0 = 0;
	cord->x1 = x1 + g_x_offset;
	cord->y1 = y1 + g_y_offset;
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
				cord = ft_set_cord(x, y, x + 1, y);
				cord->z0 = ft_strtoll(map[y][x] , NULL, 10);
				cord->z1 = ft_strtoll(map[y][x + 1] , NULL, 10);
				ft_draw_line(img, cord);
				free(cord);
			}
			if (map[y + 1] != NULL)
			{
				cord = ft_set_cord(x, y, x, y + 1);
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

void	ft_display_map(t_vars *vars)
{
	t_data	img;

	mlx_clear_window(vars->mlx, vars->win);
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	ft_display_map_helper(&img, vars->map);
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
	g_mesh_len = 1;
	g_x_offset = 0;
	g_y_offset = 100;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	mlx_key_hook(vars.win, ft_key_hook, &vars);
	mlx_mouse_hook(vars.win, ft_mouse_hook, &vars);
	vars.map = map;
	ft_display_map(&vars);
	mlx_loop(vars.mlx);
}
