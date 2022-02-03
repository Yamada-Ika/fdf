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
	char	*whole_tmp;

	inline_map = ft_strdup("");
	if (inline_map == NULL)
		return (NULL);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		whole_tmp = inline_map;
		inline_map = ft_strjoin(inline_map, line);
		if (inline_map == NULL)
		{
			all_free(line, whole_tmp, NULL, NULL);
			return (NULL);
		}
		all_free(line, whole_tmp, NULL, NULL);
	}
	return (inline_map);
}

static char	***ft_create_char_map(char *whole)
{
	char	**split_nl;
	char	***char_map;
	int		i;

	split_nl = ft_split(whole, '\n');
	if (split_nl == NULL)
		return (NULL);
	char_map = (char ***)malloc((ft_get_line_size(split_nl) + 1) * sizeof(char **));
	if (char_map == NULL)
	{
		free_strs(split_nl);
		return (NULL);
	}
	i = 0;
	while (split_nl[i] != NULL)
	{
		char_map[i] = ft_split(split_nl[i], ' ');
		if (char_map[i] == NULL)
		{
			free_tristrs(char_map);
			free_strs(split_nl);
			return (NULL);
		}
		i++;
	}
	char_map[i] = NULL;
	free_strs(split_nl);
	return (char_map);
}

static char	*ft_read_fdf(char *path)
{
	int		fd;
	char	*inline_map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	inline_map = ft_read_fdf_helper(fd);
	if (inline_map == NULL)
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	return (inline_map);
}

char	***ft_read_map(char *path)
{
	char	*inline_map;
	char	***map;

	inline_map = ft_read_fdf(path);
	if (inline_map == NULL)
		return (NULL);
	map = ft_create_char_map(inline_map);
	free(inline_map);
	return (map);
}
