#include "fdf.h"

static bool	_is_zoom_up(int button)
{
	return (button == SCROLL_UP);
}

static bool	_is_zoom_down(int button)
{
	return (button == SCROLL_DOWN);
}

static void	_set_mouse_point(t_map_info *map, int x, int y)
{
	map->mouse_x = (double)x;
	map->mouse_y = (double)y;
}

int	mouse_hook(int button, int x, int y, t_map_info *map)
{
	if (_is_zoom_up(button))
		map->zoom_rate = ZOOM_UP_STEP;
	if (_is_zoom_down(button))
		map->zoom_rate = ZOOM_DOWN_STEP;
	if (_is_zoom_up(button) || _is_zoom_down(button))
	{
		_set_mouse_point(map, x, y);
		if (!can_redisplay_map(map))
			mlx_loop_end(map->mlx);
	}
	return (0);
}
