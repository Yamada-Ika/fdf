#include "fdf.h"

static bool	is_zoom_up(int button)
{
	return (button == SCROLL_UP);
}

static bool	is_zoom_down(int button)
{
	return (button == SCROLL_DOWN);
}

static void	ft_init_mouse_point_and_zoom_rate(t_map_info *map)
{
	map->zoom_rate = 1.0;
	map->mouse_x = 0;
	map->mouse_y = 0;
}

int	ft_mouse_hook(int button, int x, int y, t_map_info *map)
{
	if (is_zoom_up(button))
		map->zoom_rate = 2.0;
	if (is_zoom_down(button))
		map->zoom_rate = 0.5;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		mlx_destroy_image(map->mlx, map->img.img);
		mlx_clear_window(map->mlx, map->win);
		map->mouse_x = (double)x;
		map->mouse_y = (double)y;
		ft_display_map(map);
		ft_init_mouse_point_and_zoom_rate(map);
	}
	return (0);
}
