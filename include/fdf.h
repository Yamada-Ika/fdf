/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:19:01 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/04 00:52:52 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <errno.h>

# define WIDTH 1000
# define HEIGHT 1000
# define OFFSET 10

// mouse
# define R_CLICK 1
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// key
# define ESCAPE 0xff1b
# define LEFT 0xff51
# define UP 0xff52
# define RIGHT 0xff53
# define DOWN 0xff54
# define I 105
# define P 112
# define C 99

# include "libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	char	***map;
	double	**matrix;
	int		mesh_len;
	int		shift_x;
	int		shift_y;
	double	zoom_rate;
	double	roll;
	double	yaw;
	int		color0;
	int		color1;
}	t_vars;

typedef struct s_2dcord
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
void	ft_create_matrix(t_vars *vars);
void	ft_set_matrix(t_vars *vars);

// free_utils.c
void	all_free(void *p1, void *p2, void *p3, void *p4);
void	free_strs(char **strs);
void	free_tristrs(char ***strs);

// error.c
void	*ft_print_error(char *message);
void	*ft_do_read_error_routine(void *p1, void *p2, void *p3, void *p4);
void	*ft_do_malloc_error_routine(void *p1, void *p2, void *p3, void *p4);
void	*ft_do_malloc_strs_error_routine(void **p1, void ***p2);

// init_struct.c
void	ft_init_vars(t_vars *vars);

// hook.c
void	ft_install_hook(t_vars *vars);
int		ft_key_hook(int keycode, t_vars *vars);
int		ft_mouse_hook(int button, int x, int y, t_vars *vars);

// hook_utils1.c
bool	is_shift_key(int keycode);
bool	is_switch_projection_key(int keycode);
bool	is_valid_key(int keycode);
bool	is_zoom_up(int button, double zoom_rate);
bool	is_zoom_down(int button, double zoom_rate);


// cord_trans.c
void	ft_trans_cord(t_2dcord *cord, t_vars *vars);
bool	ft_is_over_img_size(t_2dcord *cord);

// draw_line.c
void	ft_draw_line(t_data *img, t_2dcord *cord, t_vars *vars);

// math_utils.c
double	ft_max(double n1, double n2);
double	ft_abs(double n);

void	ft_display_map(t_vars *vars);
char	***ft_read_map(char *path);

// ft_set_projection.c
void	ft_set_isometric(t_vars *vars);
void	ft_set_parallel(t_vars *vars);
void	ft_set_conic(t_vars *vars);

// put_pixel.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
