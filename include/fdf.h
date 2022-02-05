/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyamada <iyamada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:19:01 by iyamada           #+#    #+#             */
/*   Updated: 2022/02/05 22:36:23 by iyamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <errno.h>

# define WIDTH 700
# define HEIGHT 700
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
# define X 0x78
# define Y 0x79
# define Z 0x7a
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

typedef struct s_map
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	**map_tmp;
	t_map	**map_tmp_tmp;
	int		map_row_size;
	int		map_colmun_size;
	double	**affine_matrix;
	double	**shift_matrix;
	double	**zoom_matrix;
	double	**move_origin_matrix;
	double	**move_upleftcorner_matrix;
	double	**to_upleftcorner_for_rotate_matrix;
	double	**rotate_x_matrix;
	double	**rotate_y_matrix;
	double	**rotate_z_matrix;
	double	**to_map_origin_for_rotate_matrix;
	double	**tmp_for_product;
	int		mesh_len;
	int		shift_x;
	int		shift_y;
	double	zoom_rate;
	double	mouse_x;
	double	mouse_y;
	double	roll;
	double	yaw;
	double	pitch;
	double	map_origin_x;
	double	map_origin_y;
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

// map_utils.c
int		ft_get_map_column_count(char ***map);
int		ft_get_map_row_count(char ***map);
void	ft_set_map(t_map **map_tmp, char ***map);

// create_map.c
t_map	**ft_create_map(size_t row_size, size_t column_size);

// ft_read_map.c
void	ft_read_map_tmp(char *path, t_vars *vars);

// arg_utils.c
bool	is_invalid_file_extension(char *path, char *extension);
bool	is_invalid_args(int argc, char *argv[]);


// ----------------------- matrix -----------------------
void	ft_new_matrix(t_vars *vars);
void	product_matrix(double **matrix1, double **matrix2, double **tmp_matrix);
void	ft_calc_affine_matrix(t_vars *vars);
void	set_unit_matrix(double **matrix);
void	set_trans_matrix(double **matrix, double tx, double ty, double tz);
void	set_zoom_matrix(double **matrix, double zoom_rate);
void	set_rotate_x_matrix(double **matrix, double roll);
void	set_rotate_y_matrix(double **matrix, double pitch);
void	set_rotate_z_matrix(double **matrix, double yaw);
// ----------------------- matrix -----------------------

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

// debug
void	_debug_matrix(double **matrix);
void	debug_xy(double x, double y);
void	debug_cord(t_2dcord *cord);
void	_debug_print_vars(t_vars *vars);
void	debug_map(t_map **map, size_t row_size, size_t col_size);

#endif
