#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <errno.h>

# define WIDTH 700
# define HEIGHT 700
# define ROTATION_STEP 15
# define TRANS_STEP 20.0

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
# define R 0x72
# define I 105
# define P 112
# define C 99

# include "libft.h"

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
	t_matrix		mtx;
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

// arg_utils.c
bool	is_invalid_args(int argc, char *argv[]);
bool	is_invalid_file_content(char *file_path);

// read_map.c
bool	can_read_map(char *path, t_map_info *vars);
char	*ft_read_fdf(char *path);


// ----------------------- map utils -----------------------
size_t	get_map_col_size(char ***map);
size_t	get_map_row_size(char ***map);
// ----------------------- map utils -----------------------

void	ft_init_point(t_point **map, char ***str_map);

// create_map.c
t_point	**create_points(size_t row_size, size_t col_size);

// utils.c
size_t	get_strs_elem_size(char **strs);


// ----------------------- matrix -----------------------
void	ft_new_matrix(t_map_info *map);
void	product_matrix(double **matrix1, double **matrix2, double **tmp_matrix);
void	ft_calc_affine_matrix(t_map_info *vars);
void	set_unit_matrix(double **matrix);
void	set_trans_matrix(double **matrix, double tx, double ty);
void	set_zoom_matrix(double **matrix, double zoom_rate);
void	set_rotate_x_matrix(double **matrix, double roll);
void	set_rotate_y_matrix(double **matrix, double pitch);
void	set_rotate_z_matrix(double **matrix, double yaw);
// ----------------------- matrix -----------------------

// free_utils.c
void	all_free(void *p1, void *p2, void *p3, void *p4);
void	free_strs(char **strs);
void	free_char_map(char ***map);

// error.c
void	*ft_print_error(char *message);
void	*ft_do_read_error_routine(char *p1, char *p2, char *p3, char *p4);
void	*ft_do_malloc_error_routine(char *p1, char *p2, char *p3, char *p4);
void	*ft_do_malloc_strs_error_routine(char **p1, char ***p2);

// init_struct.c
void	init_map_info(t_map_info *vars);

// hook.c
void	install_hook(t_map_info *vars);
int		ft_key_hook(int key, t_map_info *vars);
int		ft_mouse_hook(int button, int x, int y, t_map_info *vars);

// hook_utils1.c
bool	is_shift_key(int key);
bool	is_switch_projection_key(int key);
bool	is_valid_key(int key);
bool	is_rotation_key(int key);
double	degree_to_radian(int deg);

// draw_line.c
void	draw_line(t_image_info *img, t_point *map0,
			t_point *map1, double **matrix);

// cord_trans.c
void	ft_trans_cord(t_point *map0, t_point *map1, double **matrix);

// math_utils.c
double	ft_max(double n1, double n2);
double	ft_abs(double n);

void	display_map(t_map_info *vars);
void	ft_put_map_to_image(t_map_info *map);

// update_map_points.c
void	update_map_points(t_point **dst, t_point **src,
			size_t row_size, size_t col_size);

// ft_set_projection.c
void	ft_set_isometric(t_map_info *vars);
void	ft_set_parallel(t_map_info *vars);
void	ft_set_conic(t_map_info *vars);

// put_pixel.c
void	my_mlx_pixel_put(t_image_info *data, int x, int y, int color);

#endif
