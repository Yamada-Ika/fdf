#include "fdf.h"

// Update affine each product_matrix called
void	_gen_affine_matrix(t_vars *vars)
{
	// for rotate
	product_matrix(vars->affine_matrix, vars->to_map_origin_for_rotate_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->rotate_x_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->rotate_y_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->rotate_z_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->to_upleftcorner_for_rotate_matrix, vars->tmp_for_product);

	// for zoom
	product_matrix(vars->affine_matrix, vars->move_origin_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->zoom_matrix, vars->tmp_for_product);
	product_matrix(vars->affine_matrix, vars->move_upleftcorner_matrix, vars->tmp_for_product);

	// for shift
	product_matrix(vars->affine_matrix, vars->shift_matrix, vars->tmp_for_product);

	// product_matrix(vars->affine_matrix, vars->to_2d_matrix);
	fprintf(stderr, "affine_matrix\n");
	_debug_matrix(vars->affine_matrix);
}

void	ft_calc_affine_matrix(t_vars *vars)
{
	vars->map_origin_x = vars->map[vars->map_row_size/2][vars->map_column_size/2].x;
	vars->map_origin_y = vars->map[vars->map_row_size/2][vars->map_column_size/2].y;
	fprintf(stderr, "+++++++ %5f, %5f\n", vars->map_origin_x, vars->map_origin_y);

	set_trans_matrix(vars->move_upleftcorner_matrix, -vars->mouse_x, -vars->mouse_y, 0.0);
	fprintf(stderr, "=== move_upleftcorner_matrix\n");
	_debug_matrix(vars->move_upleftcorner_matrix);

	set_zoom_matrix(vars->zoom_matrix, vars->zoom_rate);
	fprintf(stderr, "=== zoom_matrix\n");
	_debug_matrix(vars->zoom_matrix);

	set_trans_matrix(vars->move_origin_matrix, vars->mouse_x, vars->mouse_y, 0.0);
	fprintf(stderr, "=== move_origin_matrix\n");
	_debug_matrix(vars->move_origin_matrix);

	set_trans_matrix(vars->shift_matrix, vars->shift_x, vars->shift_y, 0.0);
	fprintf(stderr, "=== shift_matrix\n");
	_debug_matrix(vars->shift_matrix);

	set_trans_matrix(vars->to_upleftcorner_for_rotate_matrix, -vars->map_origin_x, -vars->map_origin_y, 0.0);
	fprintf(stderr, "=== to_upleftcorner_for_rotate_matrix\n");
	_debug_matrix(vars->to_upleftcorner_for_rotate_matrix);

	set_rotate_x_matrix(vars->rotate_x_matrix, vars->roll);
	fprintf(stderr, "=== rotate_x_matrix\n");
	_debug_matrix(vars->rotate_x_matrix);

	set_rotate_y_matrix(vars->rotate_y_matrix, vars->pitch);
	fprintf(stderr, "=== rotate_y_matrix\n");
	_debug_matrix(vars->rotate_y_matrix);

	set_rotate_z_matrix(vars->rotate_z_matrix, vars->yaw);
	fprintf(stderr, "=== rotate_z_matrix\n");
	_debug_matrix(vars->rotate_z_matrix);

	set_trans_matrix(vars->to_map_origin_for_rotate_matrix, vars->map_origin_x, vars->map_origin_y, 0.0);
	fprintf(stderr, "=== to_map_origin_for_rotate_matrix\n");
	_debug_matrix(vars->to_map_origin_for_rotate_matrix);

	set_unit_matrix(vars->affine_matrix);
	_gen_affine_matrix(vars);
}
