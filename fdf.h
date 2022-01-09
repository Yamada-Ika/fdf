/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:19:01 by iyamada           #+#    #+#             */
/*   Updated: 2022/01/09 04:11:32 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define WIDTH 1000
#define HEIGHT 1000
#define OFFSET 10

// mouse
#define R_CLICK 1
#define SCROLL_UP 4
#define SCROLL_DOWN 5

// key
#define ESCAPE 0xff1b
#define LEFT 0xff51
#define UP 0xff52
#define RIGHT 0xff53
#define DOWN 0xff54
#define I 105
#define P 112
#define C 99

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	***map;
	int		mesh_len;
	int		shift_x;
	int		shift_y;
	double	x_angle;
	double	z_angle;
	int		color0;
	int		color1;
}	t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_data;

typedef struct	s_2dcord
{
	double	x0;
	double	y0;
	double	z0;
	double	x1;
	double	y1;
	double	z1;
}	t_2dcord;

#endif
