#include "fdf.h"

static bool	is_invalid_color(char **content)
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
			if (color_val < 0 || 0xFFFFFF < color_val
				|| (*end != ' ' && *end != '\0'))
				return (true);
			comma_at = ft_strchr(comma_at, ',');
		}
		i++;
	}
	return (false);
}

static bool	is_rectangle_map(char **content)
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
			return (false);
		elem_count = get_strs_elem_size(strs);
		free_strs(strs);
		if (i > 0 && elem_count != old_elem_count)
			return (false);
		old_elem_count = elem_count;
		i++;
	}
	return (true);
}

static bool	_is_invalid_char_in_strs_elem(char **strs)
{
	char	*end;
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_strtoll(strs[i], &end, 10);
		if (*end != '\0' && *end != ',')
			return (true);
		i++;
	}
	return (false);
}

static bool	is_invalid_height(char **content)
{
	char	**strs;
	size_t	i;

	i = 0;
	while (content[i] != NULL)
	{
		strs = ft_split(content[i], ' ');
		if (strs == NULL)
			return (true);
		if (_is_invalid_char_in_strs_elem(strs))
		{
			free_strs(strs);
			return (true);
		}
		free_strs(strs);
		i++;
	}
	return (false);
}

bool	is_invalid_file_content(char *file_path)
{
	char	*content;
	char	**content_strs;
	bool	is_invalid;

	content = read_inline_map(file_path);
	if (content == NULL)
		return (true);
	content_strs = ft_split(content, '\n');
	free(content);
	if (content_strs == NULL)
		return (true);
	is_invalid = false;
	if (content_strs[0] == NULL)
		is_invalid = true;
	if (!is_invalid && !is_rectangle_map(content_strs))
		is_invalid = true;
	if (!is_invalid && is_invalid_height(content_strs))
		is_invalid = true;
	if (!is_invalid && is_invalid_color(content_strs))
		is_invalid = true;
	free_strs(content_strs);
	return (is_invalid);
}
