#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <errno.h>

// image size
# define WIDTH 700
# define HEIGHT 700

// mouse
# define R_CLICK 1
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// keycode
# define ESCAPE 0xff1b
# define LEFT 0xff51
# define UP 0xff52
# define RIGHT 0xff53
# define DOWN 0xff54
# define X 0x78
# define Y 0x79
# ifdef __MACH__
#  define Z 0x7a
# endif
# ifdef __linux__
#  define Z 0x77
# endif

// map meta info
# define ROTATION_STEP 15
# define TRANS_STEP 20.0
# define ZOOM_UP_STEP 2.0
# define ZOOM_DOWN_STEP 0.5

typedef struct s_image_info
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_image_info;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}	t_point;

typedef struct s_matrix
{
	double	**affine;
	double	**shift;
	double	**zoom;
	double	**move_cursor;
	double	**to_corner_for_zoom;
	double	**to_corner_for_rotate;
	double	**rotate_x;
	double	**rotate_y;
	double	**rotate_z;
	double	**move_map_origin;
	double	**tmp_mtx;
}	t_matrix;

typedef struct s_map_info
{
	void			*mlx;
	void			*win;
	t_image_info	img;
	t_point			**points;
	t_point			**for_update;
	size_t			row_size;
	size_t			col_size;
	t_matrix		matrix;
	double			shift_x;
	double			shift_y;
	double			zoom_rate;
	double			mouse_x;
	double			mouse_y;
	double			roll;
	double			yaw;
	double			pitch;
	double			origin_x;
	double			origin_y;
}	t_map_info;

// help_option.c
bool	is_help_option(int argc, char *argv[]);
int		print_usage(void);

// arg_utils.c
bool	is_invalid_args(int argc, char *argv[]);
bool	is_invalid_file_content(char *file_path);

// read_map.c
bool	can_read_map(char *path, t_map_info *vars);
char	*read_inline_map(char *path);

// get_map_size.c
size_t	get_map_col_size(char ***map);
size_t	get_map_row_size(char ***map);

// create_points.c
t_point	**create_points(size_t row_size, size_t col_size);

// init_points.c
void	init_points(t_point **map, char ***str_map);

// init_struct.c
bool	can_init_map_info(t_map_info *vars);

// can_init_mlx.c
bool	can_init_mlx(t_map_info *map);

// hook.c
void	install_hook(t_map_info *vars);
int		key_hook(int key, t_map_info *vars);
int		mouse_hook(int button, int x, int y, t_map_info *vars);
int		expose_hook(t_map_info *map);

// hook_utils1.c
bool	is_shift_key(int key);
bool	is_switch_projection_key(int key);
bool	is_valid_key(int key);
bool	is_rotation_key(int key);
double	degree_to_radian(int deg);

// display_default_projection.c
bool	can_display_default_projection(t_map_info *map);

// display_map.c
bool	can_display_map(t_map_info *vars);
void	put_map_to_image(t_map_info *map);

// can_redisplay_map.c
bool	can_redisplay_map(t_map_info *map);

// update_map_points.c
void	update_map_points(t_point **dst, t_point **src,
			size_t row_size, size_t col_size);

// utils.c
size_t	get_strs_elem_size(char **strs);

// calc_affine_matrix.c
void	calc_affine_matrix(t_map_info *vars);

// new_matrix.c
bool	can_new_matrix(t_map_info *map);

// product_matrix.c
void	product_matrix(double **matrix1, double **matrix2, double **tmp_matrix);

// set_matrix1.c set_matrix2.c
void	set_unit_matrix(double **matrix);
void	set_trans_matrix(double **matrix, double tx, double ty);
void	set_zoom_matrix(double **matrix, double zoom_rate);
void	set_rotate_x_matrix(double **matrix, double roll);
void	set_rotate_y_matrix(double **matrix, double pitch);
void	set_rotate_z_matrix(double **matrix, double yaw);

// free_utils.c
void	all_free(void *p1, void *p2, void *p3, void *p4);
void	free_strs(char **strs);
void	free_char_map(char ***map);

// error.c
void	*ft_do_read_error_routine(char *p1, char *p2, char *p3, char *p4);
void	*ft_do_malloc_error_routine(char *p1, char *p2, char *p3, char *p4);
void	*ft_do_malloc_strs_error_routine(char **p1, char ***p2);

// error2.c
int		print_error(char *message);

// draw_line.c
void	draw_line(t_image_info *img, t_point *map0,
			t_point *map1, double **matrix);

// cord_trans.c
void	trans_point(t_point *map0, t_point *map1, double **matrix);

// math_utils.c
double	ft_max(double n1, double n2);
double	ft_abs(double n);

// put_pixel.c
void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color);

// delete
void	delete_mlx(t_map_info *map);
void	delete_map(t_map_info *map);
void	delete_points(t_point **points, size_t row_size);

// # define ft_split(n1, n2) test1(n1, n2)
// char	**test1(char *s, char c);
// # define ft_calloc(n1, n2) test2(n1, n2)
// void	*test2(size_t n, size_t size);
// # define mlx_init() test3()
// void	*test3(void);
// # define mlx_new_window(n1, n2, n3, n4) test4(n1, n2, n3, n4)
// void	*test4(void *xvar, int size_x, int size_y, char *title);
// # define mlx_new_image(n1, n2, n3) test5(n1, n2, n3)
// void	*test5(void *xvar,int width, int height);

#endif
