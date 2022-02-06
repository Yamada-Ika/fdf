#include "fdf.h"

bool	is_shift_key(int key)
{
	return ((key == RIGHT || key == LEFT
			|| key == UP || key == DOWN));
}

bool	is_switch_projection_key(int key)
{
	return ((key == I || key == P
			|| key == C));
}

bool	is_valid_key(int key)
{
	return (is_shift_key(key)
		|| is_switch_projection_key(key)
		|| key == X || key == Y || key == Z);
}

bool	is_zoom_up(int button, double zoom_rate)
{
	return (button == SCROLL_UP);
}

bool	is_zoom_down(int button, double zoom_rate)
{
	return (button == SCROLL_DOWN);
}
