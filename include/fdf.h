/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:19:01 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/03 00:57:05 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "mlx.h"
#include <stdio.h>
#include <math.h>

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

#include "libft.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	***map;
	double	**affine_matrix;
	int		mesh_len;
	int		shift_x;
	int		shift_y;
	double	zoom_rate;
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

// arg_utils.c
bool	is_invalid_file_extension(char *path, char *extension);
bool	is_invalid_args(int argc, char *argv[]);

// matrix_utils.c
void	ft_create_affine_matrix(t_vars *vars);
void	ft_set_affine_matrix(t_vars *vars);

// init_struct.c
void	ft_init_vars(t_vars *vars);

// hook.c
void	ft_install_hook(t_vars *vars);

void	ft_display_map(t_vars *vars);
char	***ft_read_map(char *path);

// ft_set_projection.c
void	ft_set_isometric(t_vars *vars);
void	ft_set_parallel(t_vars *vars);
void	ft_set_conic(t_vars *vars);

// hook.c
int	ft_key_hook(int keycode, t_vars *vars);
int	ft_mouse_hook(int button, int x, int y, t_vars *vars);

#endif
