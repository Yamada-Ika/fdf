/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
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

static char	*ft_read_fdf_helper(int fd)
{
	char	*line;
	char	*whole;
	char	*whole_tmp;

	whole = ft_strdup("");
	if (whole == NULL)
		return (NULL);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		whole_tmp = whole;
		whole = ft_strjoin(whole, line);
		free(line);
		free(whole_tmp);
	}
	return (whole);
}

static char	*ft_read_fdf(char *path)
{
	int		fd;
	char	*fdf;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	fdf = ft_read_fdf_helper(fd);
	if (fdf == NULL)
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	return (fdf);
}

static char	***ft_create_char_map(char *whole)
{
	char	**split_nl;
	char	***char_map;
	int	i;

	split_nl = ft_split(whole, '\n');
	if (split_nl == NULL)
		return (NULL);
	char_map = (char ***)malloc((ft_get_line_size(split_nl) + 1) * sizeof(char **));
	if (char_map == NULL)
		return (NULL);
	i = 0;
	while (split_nl[i] != NULL)
	{
		char_map[i] = ft_split(split_nl[i], ' ');
		if (char_map[i] == NULL)
			return (NULL);
		i++;
	}
	char_map[i] = NULL;
	return (char_map);
}

char	***ft_create_map(char *path)
{
	char	*whole;

	whole = ft_read_fdf(path);
	if (whole == NULL)
		return (NULL);
	return (ft_create_char_map(whole));
}
