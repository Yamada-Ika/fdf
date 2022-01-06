/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 15:44:19 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/06 14:36:03 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

char	*ft_read_fdf_helper(int fd);
char	*ft_read_fdf(char *path);
int		ft_get_line_size(char **s);
char	***ft_create_char_map(char *whole);
void	ft_display_char_map(char ***map);
char	***ft_create_map(char *whole);

int	ft_get_map_column_count(char ***map);
int	ft_get_map_raw_count(char ***map);
int	ft_get_map_z_max(char ***map);

#endif
