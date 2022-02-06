#include "libft.h"
#include "get_next_line.h"

// for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fdf.h"

static char	*ft_read_fdf_helper(int fd)
{
	char	*line;
	char	*inline_map;
	char	*tmp_for_free;

	inline_map = ft_strdup("");
	if (inline_map == NULL)
		return (ft_print_error("Cannot allocate memmory"));
	while (true)
	{
		errno = 0;
		line = get_next_line(fd);
		if (errno != 0)
			return (ft_do_read_error_routine(line, inline_map, NULL, NULL));
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

static char	***ft_generate_map(char *inline_map)
{
	char	**map_strs;
	char	***map;
	int		i;

	map_strs = ft_split(inline_map, '\n');
	if (map_strs == NULL)
		return (ft_print_error("Cannot allocate memmory"));
	map = (char ***)malloc((get_strs_elem_size(map_strs) + 1)
			* sizeof(char **));
	if (map == NULL)
		return (ft_do_malloc_strs_error_routine(map_strs, NULL));
	i = 0;
	while (map_strs[i] != NULL)
	{
		map[i] = ft_split(map_strs[i], ' ');
		if (map[i] == NULL)
			return (ft_do_malloc_strs_error_routine(map_strs, map));
		i++;
	}
	map[i] = NULL;
	free_strs(map_strs);
	return (map);
}

char	*ft_read_fdf(char *path)
{
	int		fd;
	char	*inline_map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_print_error("Cannot open file"));
	inline_map = ft_read_fdf_helper(fd);
	if (inline_map == NULL)
	{
		close(fd);
		return (NULL);
	}
	if (close(fd) == -1)
	{
		free(inline_map);
		return (ft_print_error("Cannot close file"));
	}
	return (inline_map);
}

static char	***read_map(char *path)
{
	char	*inline_map;
	char	***map;

	inline_map = ft_read_fdf(path);
	if (inline_map == NULL)
		return (NULL);
	map = ft_generate_map(inline_map);
	free(inline_map);
	return (map);
}

void	ft_read_map(char *path, t_map_info *map)
{
	char	***char_map;
	size_t	row_size;
	size_t	col_size;

	char_map = read_map(path);
	if (char_map == NULL)
	{
		map->points = NULL;
		return ;
	}
	row_size = get_map_row_size(char_map);
	col_size = get_map_col_size(char_map);
	map->points = ft_create_map(row_size, col_size);
	map->for_update = ft_create_map(row_size, col_size);
	ft_init_point(map->points, char_map);
	free_char_map(char_map);
	map->row_size = row_size;
	map->col_size = col_size;
}
