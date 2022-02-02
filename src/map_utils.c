/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 15:42:53 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/03 01:32:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_line_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

void	ft_display_char_map(char ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
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
