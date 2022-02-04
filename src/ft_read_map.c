/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:44:41 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/07 18:15:41 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

// map size
#include "map_utils.h"

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
	map = (char ***)malloc((ft_get_line_size(map_strs) + 1) * sizeof(char **));
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

static char	*ft_read_fdf(char *path)
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

char	***ft_read_map(char *path)
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

t_map	**ft_read_map_tmp(char *path, t_vars *vars)
{
	char	***char_map;
	t_map	**map;
	size_t	row_size;
	size_t	colmun_size;

	char_map = ft_read_map(path);
	if (char_map == NULL)
		return (NULL);
	row_size = ft_get_map_row_count(char_map);
	colmun_size = ft_get_map_column_count(char_map);
	map = ft_create_map(row_size, colmun_size);
	ft_set_map(map, char_map);
	vars->map_row_size = row_size;
	vars->map_colmun_size = colmun_size;
	free_tristrs(char_map);
	return (map);
}
