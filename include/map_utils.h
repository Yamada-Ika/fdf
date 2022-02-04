/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 15:44:19 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/04 19:14:46 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

int	ft_get_line_size(char **s);
int	ft_get_map_column_count(char ***map);
int	ft_get_map_row_count(char ***map);
int	ft_get_map_z_max(char ***map);

#endif
