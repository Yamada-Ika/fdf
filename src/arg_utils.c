#include "fdf.h"

bool	is_invalid_file_extension(char *path, char *extension)
{
	char	*dot_at;

	dot_at = ft_strrchr(path, '.');
	if (dot_at == NULL)
		return (true);
	dot_at++;
	if (ft_strcmp(dot_at, extension) != 0)
		return (true);
	else
		return (false);
}

bool	is_invalid_args(int argc, char *argv[])
{
	if (argc != 2)
		return (true);
	if (is_invalid_file_extension(argv[1], "fdf"))
		return (true);
	else
		return (false);
}
