#include "fdf.h"

/*
Update affine each product_matrix called
*/
void	_gen_affine_matrix(t_matrix *mtx)
{
	product_matrix(mtx->affine, mtx->move_map_origin, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->rotate_z, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->rotate_y, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->rotate_x, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->to_corner_for_rotate, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->move_cursor, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->zoom, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->to_corner_for_zoom, mtx->tmp_mtx);
	product_matrix(mtx->affine, mtx->shift, mtx->tmp_mtx);
}

/*
Calculation mtx for cordinate transformation.
For rotation,
	1. Move to Up-left corner in window. Adjust map center to (0, 0).
	2. Rotate
	3. Move to map center (map_center_x, map_center_y).
For zoom,
	1. Move to Up-left corner in window. Adjust mouse point to (0, 0).
	2. Zoom
	3. Move to mouse center (mouse_center_x, mouse_center_y).
For shift,
	1. shift
*/
void	ft_calc_affine_matrix(t_map_info *map)
{
	t_matrix	mtx;

	mtx = map->mtx;
	set_trans_matrix(mtx.to_corner_for_zoom, -map->mouse_x, -map->mouse_y);
	set_zoom_matrix(mtx.zoom, map->zoom_rate);
	set_trans_matrix(mtx.move_cursor, map->mouse_x, map->mouse_y);
	set_trans_matrix(mtx.shift, map->shift_x, map->shift_y);
	set_trans_matrix(mtx.to_corner_for_rotate, -map->origin_x, -map->origin_y);
	set_rotate_x_matrix(mtx.rotate_x, map->roll);
	set_rotate_y_matrix(mtx.rotate_y, map->pitch);
	set_rotate_z_matrix(mtx.rotate_z, map->yaw);
	set_trans_matrix(mtx.move_map_origin, map->origin_x, map->origin_y);
	set_unit_matrix(mtx.affine);
	_gen_affine_matrix(&mtx);
}
