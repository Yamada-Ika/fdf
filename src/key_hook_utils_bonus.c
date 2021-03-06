#include "fdf.h"

bool	is_shift_key(int key)
{
	return ((key == RIGHT || key == LEFT
			|| key == UP || key == DOWN));
}

bool	is_rotation_key(int key)
{
	return (key == X || key == Y || key == Z);
}

bool	is_valid_key(int key)
{
	return (is_shift_key(key) || is_rotation_key(key));
}
