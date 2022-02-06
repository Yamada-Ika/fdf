/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 04:45:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/06 17:06:29 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_isometric(t_map_info *vars)
{
	vars->roll = 0.615;
	vars->yaw = -0.8;
}

void	ft_set_parallel(t_map_info *vars)
{
	vars->roll = 0.615;
	vars->yaw = -0.8;
}

void	ft_set_conic(t_map_info *vars)
{
	vars->roll = 1.57;
	vars->yaw = 0.0;
}
