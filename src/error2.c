#include "fdf.h"

int	print_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	return (1);
}
