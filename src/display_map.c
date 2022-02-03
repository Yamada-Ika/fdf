#include "fdf.h"

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

void	ft_set_z_color_helper1(t_2dcord *cord, t_vars *vars, int y, int x)
{
	char	*color;

	color = "";
	cord->z1 = ft_strtoll(vars->map[y][x], &color, 10);
	if (color[0] == ',')
		vars->color1 = ft_strtoll(++color, NULL, 16);
	else
		vars->color1 = 0xFFFFFF;
}

void	ft_set_z_color_helper0(t_2dcord *cord, t_vars *vars, int y, int x)
{
	char	*color;

	color = "";
	cord->z0 = ft_strtoll(vars->map[y][x], &color, 10);
	if (color[0] == ',')
		vars->color0 = ft_strtoll(++color, NULL, 16);
	else
		vars->color0 = 0xFFFFFF;
}

void	ft_display_map_helper(t_data *img, t_vars *vars)
{
	int			y;
	int			x;
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
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_len, &img.endian);
	ft_set_matrix(vars);
	ft_display_map_helper(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	vars->img = img;
}
