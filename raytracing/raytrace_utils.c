#include "../minirt.h"

t_object
	*get_object(t_object *obj_ptr, int obj_id)
{
	while (obj_ptr->obj_id != obj_id && obj_ptr->next_object != NULL)
		obj_ptr = obj_ptr->next_object;
	if (obj_ptr->obj_id == obj_id)
		return (obj_ptr);
	return (NULL);
}

void
	set_pov_plan(double *orient_vec, t_ray *ray_ptr)
{
	vec_copy(orient_vec, ray_ptr->vec_w, 3);
	ray_ptr->vec_v[0] = 0;
	ray_ptr->vec_v[1] = 1;
	ray_ptr->vec_v[2] = 0;
	if (ray_ptr->vec_w[0] == 0.0 && ray_ptr->vec_w[2] == 0.0) //&& (ray_ptr->vec_w[1] == -1.0 || ray_ptr->vec_w[1] == 1.0)
	{
		printf("Oupsi!\n");
		ray_ptr->vec_v[0] =  cos(RADIAN(95));
		ray_ptr->vec_v[1] *= sin(RADIAN(95));
	}
	// {
	//	   ray_ptr->vec_v[0] = -1;
	//	   ray_ptr->vec_v[1] = 0;
	//	   ray_ptr->vec_v[2] = 0;
	// }
	cross_product(ray_ptr->vec_u, ray_ptr->vec_v, ray_ptr->vec_w);
	cross_product(ray_ptr->vec_v, ray_ptr->vec_w, ray_ptr->vec_u);
	vec_normalize(ray_ptr->vec_u, 3);
	vec_normalize(ray_ptr->vec_v, 3);
}

void
	init_func_arr(t_args_func *func_arr)
{
	func_arr[sphere] = sphere_intersect;
	func_arr[plane] = plane_intersect;
	func_arr[square] = square_intersect;
	func_arr[triangle] = triangle_intersect;
	func_arr[cylinder] = cylinder_intersect;
}

void
	set_camera_plan(t_param *p_ptr, t_ray *ray_ptr)
{
	ray_ptr->screen_dist = (((double)p_ptr->res_x) / 2.0) / \
	tan(RADIAN(((double)p_ptr->current_camera->fov) / (2.0)));
	vec_copy(p_ptr->current_camera->coord1, ray_ptr->origin, 3);
	set_pov_plan(p_ptr->current_camera->coord2, ray_ptr);
	vec_scalarprod(ray_ptr->vec_w, ray_ptr->screen_dist, 3);
	vec_copy(ray_ptr->vec_u, ray_ptr->unit_u, 3);
	vec_copy(ray_ptr->vec_v, ray_ptr->unit_v, 3);
}

double
	max_d(double nb1, double nb2)
{
	if (nb1 > nb2)
		return (nb1);
	return (nb2);
}
