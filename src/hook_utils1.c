#include "fdf.h"

bool	is_shift_key(int keycode)
{
	return ((keycode == RIGHT || keycode == LEFT
			|| keycode == UP || keycode == DOWN));
}

bool	is_switch_projection_key(int keycode)
{
	return ((keycode == I || keycode == P
			|| keycode == C));
}

bool	is_valid_key(int keycode)
{
	return (is_shift_key(keycode)
		|| is_switch_projection_key(keycode));
}

bool	is_zoom_up(int button, double zoom_rate)
{
	return (button == SCROLL_UP && zoom_rate < 100);
}

bool	is_zoom_down(int button, double zoom_rate)
{
	return (button == SCROLL_DOWN && zoom_rate > 0.1);
}
