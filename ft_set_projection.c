/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 04:45:46 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/09 05:04:27 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_isometric(t_vars *vars)
{
	vars->x_angle = 0.615;
	vars->z_angle = -0.8;
}

void	ft_set_parallel(t_vars *vars)
{
	vars->x_angle = 0.615;
	vars->z_angle = -0.8;
}

void	ft_set_conic(t_vars *vars)
{
	vars->x_angle = 1.57;
	vars->z_angle = 0.0;
}
