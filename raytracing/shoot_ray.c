#include "../minirt.h"

void
	fill_window(t_param *p_ptr, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < p_ptr->step && x < p_ptr->res_x)
	{
		j = 0;
		while (j < p_ptr->step && y < p_ptr->res_y)
		{
			my_mlx_pixel_put(p_ptr->pix_ptr, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static int
	set_ray_params(t_param *p_ptr, t_ray *ray_ptr, double obj_dist)
{
	int color;

	if (obj_dist > 0.0)
	{
		vec_copy(ray_ptr->direction, ray_ptr->vec_intersect, 3);
		vec_scalarprod(ray_ptr->vec_intersect, obj_dist, 3);
		vec_addition(ray_ptr->vec_intersect, ray_ptr->origin, \
		ray_ptr->vec_intersect, 3);
		set_normal(p_ptr->closest_surface, ray_ptr);
		color = get_color(p_ptr, ray_ptr);
	}
	else
		color = 0;
	return (color);
}

double
	set_closest(t_param *p_ptr, t_ray *ray_ptr)
{
	t_object	*surface;
	double		obj_dist;
	double		store;

	obj_dist = 0.0;
	surface = p_ptr->object;
	while (surface)
	{
		if (surface->obj_id < DIFF_SURFACE)
		{
			store = p_ptr->func_arr_ptr[surface->obj_id](ray_ptr, surface);
			if (store > 0.0 && (store < obj_dist || obj_dist == 0.0))
			{
				obj_dist = store;
				p_ptr->closest_surface = surface;
			}
		}
		surface = surface->next_object;
	}
	return (obj_dist);
}

void
	ray_trace(t_param *p_ptr)
{
	t_ray		ray;
	int			x;
	int			y;

	set_camera_plan(p_ptr, &ray);
	x = 0;
	while (x < p_ptr->res_x && !(y = 0))
	{
		ray.vec_u[0] = ray.unit_u[0] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
		ray.vec_u[1] = ray.unit_u[1] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
		ray.vec_u[2] = ray.unit_u[2] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
		while (y < p_ptr->res_y)
		{
			ray.vec_v[0] = ray.unit_v[0] * ((double)p_ptr->res_y / 2.0 - y);
			ray.vec_v[1] = ray.unit_v[1] * ((double)p_ptr->res_y / 2.0 - y);
			ray.vec_v[2] = ray.unit_v[2] * ((double)p_ptr->res_y / 2.0 - y);
			vec_addition(ray.direction, ray.vec_u, ray.vec_v, 3);
			vec_addition(ray.direction, ray.direction, ray.vec_w, 3);
			vec_normalize(ray.direction, 3);
			fill_window(p_ptr, set_ray_params(p_ptr, &ray, \
			set_closest(p_ptr, &ray)), x, y);
			y += p_ptr->step;
		}
		x += p_ptr->step;
	}
}
