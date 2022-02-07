#include "fdf.h"

bool	is_help_option(int argc, char *argv[])
{
	if (argc != 2)
		return (false);
	if (ft_strcmp(argv[1], "-h") == 0
		|| ft_strcmp(argv[1], "--h") == 0
		|| ft_strcmp(argv[1], "-help") == 0
		|| ft_strcmp(argv[1], "--help") == 0)
		return (true);
	else
		return (false);
}

int	print_usage(void)
{
	ft_putstr("Usage: ./fdf file.fdf\n\n");
	ft_putstr("File format description:\n");
	ft_putstr("\tThe fdf file must contain integers separated by spaces.\n");
	ft_putstr("\tYou can also specify a color code by ");
	ft_putstr("connecting a comma after the number.\n\n");
	ft_putstr("Example:\n");
	ft_putstr("\t0,0xff00 1          2 3\n");
	ft_putstr("\t0        1,0xffffff 2 3\n");
	ft_putstr("\t0        1          2 3\n\n");
	return (0);
}
