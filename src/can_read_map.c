#include "fdf.h"

static char	*read_inline_map_helper(int fd)
{
	char	*line;
	char	*inline_map;
	char	*tmp_for_free;

	inline_map = ft_strdup("");
	if (inline_map == NULL)
		return (NULL);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp_for_free = inline_map;
		inline_map = ft_strjoin(inline_map, line);
		if (inline_map == NULL)
			return (ft_do_malloc_error_routine(line, tmp_for_free, NULL, NULL));
		all_free(line, tmp_for_free, NULL, NULL);
	}
	return (inline_map);
}

static char	***gen_map(char *inline_map)
{
	char	**map_strs;
	char	***map;
	int		i;

	map_strs = ft_split(inline_map, '\n');
	if (map_strs == NULL)
		return (NULL);
	map = (char ***)malloc((get_strs_elem_size(map_strs) + 1)
			* sizeof(char **));
	if (map == NULL)
		return (ft_do_malloc_strs_error_routine(map_strs, NULL));
	i = 0;
	while (map_strs[i] != NULL)
	{
		map[i] = ft_split(map_strs[i], ' ');
		if (map[i] == NULL)
			return (NULL);
		i++;
	}
	map[i] = NULL;
	free_strs(map_strs);
	return (map);
}

char	*read_inline_map(char *path)
{
	int		fd;
	char	*inline_map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	inline_map = read_inline_map_helper(fd);
	if (inline_map == NULL)
	{
		close(fd);
		return (NULL);
	}
	if (close(fd) == -1)
	{
		free(inline_map);
		return (NULL);
	}
	return (inline_map);
}

static char	***_read_map(char *path)
{
	char	*inline_map;
	char	***map;

	inline_map = read_inline_map(path);
	if (inline_map == NULL)
		return (NULL);
	map = gen_map(inline_map);
	free(inline_map);
	return (map);
}

bool	can_read_map(char *path, t_map_info *map)
{
	char	***char_map;
	size_t	row_size;
	size_t	col_size;

	char_map = _read_map(path);
	if (char_map == NULL)
		return (false);
	row_size = get_map_row_size(char_map);
	col_size = get_map_col_size(char_map);
	map->points = create_points(row_size, col_size);
	map->for_update = create_points(row_size, col_size);
	if (map->points == NULL || map->for_update == NULL)
	{
		delete_points(map->points, row_size);
		delete_points(map->for_update, row_size);
		free_char_map(char_map);
		return (false);
	}
	init_points(map->points, char_map);
	free_char_map(char_map);
	map->row_size = row_size;
	map->col_size = col_size;
	return (true);
}
