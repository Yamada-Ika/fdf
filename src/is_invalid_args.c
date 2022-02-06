#include "fdf.h"

static bool	_is_invalid_file_extension(char *path, char *extension)
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

bool	is_invalid_color(char **content)
{
	size_t		i;
	char		*comma_at;
	char		*end;
	long long	color_val;

	i = 0;
	while (content[i] != NULL)
	{
		comma_at = ft_strchr(content[i], ',');
		while (comma_at != NULL)
		{
			color_val = ft_strtoll(++comma_at, &end, 16);
			if (color_val < 0 || 0xFFFFFF < color_val || (*end != ' ' && *end != '\0'))
				return (true);
			comma_at = ft_strchr(comma_at, ',');
		}
		i++;
	}
	return (false);
}

size_t	get_strs_elem_size(char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size] != NULL)
		size++;
	return (size);
}

bool	is_rectangle_map(char **content)
{
	char	**strs;
	size_t	elem_count;
	size_t	old_elem_count;
	size_t	i;

	i = 0;
	while (content[i] != NULL)
	{
		strs = ft_split(content[i], ' ');
		if (strs == NULL)
		{
			ft_print_error("Cannot allocate memmory");
			return (false);
		}
		elem_count = get_strs_elem_size(strs);
		free_strs(strs);
		if (i > 0 && elem_count != old_elem_count)
			return (false);
		old_elem_count = elem_count;
		i++;
	}
	return (true);
}

bool	is_invalid_height(char **content)
{
	char	**strs;
	char	*end;
	size_t	i;
	size_t	j;

	i = 0;
	while (content[i] != NULL)
	{
		strs = ft_split(content[i], ' ');
		if (strs == NULL)
		{
			ft_print_error("Cannot allocate memmory");
			return (true);
		}
		j = 0;
		while (strs[j] != NULL)
		{
			ft_strtoll(strs[j], &end, 10);
			if (*end != '\0')
			{
				free_strs(strs);
				return (true);
			}
			j++;
		}
		free_strs(strs);
		i++;
	}
	return (true);
}

bool	is_invalid_file_content(char *file_path)
{
	char	*content;
	char	**content_strs;

	content = ft_read_fdf(file_path);
	if (content == NULL)
		return (true);
	content_strs = ft_split(content, '\n');
	if (content_strs == NULL)
	{
		free(content);
		ft_print_error("Cannot allocate memmory");
		return (true);
	}
	free(content);
	if (!is_rectangle_map(content_strs))
	{
		free_strs(content_strs);
		return (true);
	}
	if (is_invalid_height(content_strs))
	{
		free_strs(content_strs);
		return (true);
	}
	if (is_invalid_color(content_strs))
	{
		free_strs(content_strs);
		return (true);
	}
	else
	{
		free_strs(content_strs);
		return (false);
	}
}

bool	is_invalid_args(int argc, char *argv[])
{
	if (argc != 2)
		return (true);
	if (_is_invalid_file_extension(argv[1], "fdf"))
		return (true);
	if (is_invalid_file_content(argv[1]))
		return (true);
	else
		return (false);
}
