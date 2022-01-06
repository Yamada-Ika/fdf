/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 15:42:53 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/06 14:39:14 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
// for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_read_fdf_helper(int fd)
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

char	*ft_read_fdf(char *path)
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

int	ft_get_line_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

char	***ft_create_char_map(char *whole)
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

void	ft_display_char_map(char ***map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != NULL)
		{
			ft_putstr(map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

char	***ft_create_map(char *whole)
{
	return (ft_create_char_map(whole));
}


int	ft_get_map_column_count(char ***map)
{
	int	count;

	count = 0;
	while (map[0][count] != NULL)
		count++;
	return (count);
}

int	ft_get_map_raw_count(char ***map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

int	ft_get_map_z_max(char ***map)
{
	int	i;
	int	j;
	int	z_max;

	i = 0;
	z_max = INT_MIN;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != NULL)
		{
			if (z_max < ft_strtoll(map[i][j], NULL, 10))
				z_max = ft_strtoll(map[i][j], NULL, 10);
			j++;
		}
		i++;
	}
	return (z_max);
}
