/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:08:55 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:08:56 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	fill_window_save(t_param *p_ptr, int color, int x)
{
	int	i;

	write(p_ptr->fd_bmp, &color, 3);
	if (x == 1)
	{
		i = (p_ptr->res_x % 4);
		while (i-- > 0)
			write(p_ptr->fd_bmp, "\0", 1);
	}
}

void
	fill_window(t_param *p_ptr, int color, int x, int y)
{
	int i;
	int j;

	i = 0;
	if (p_ptr->save)
		fill_window_save(p_ptr, color, x);
	else
	{
		while (i < p_ptr->step && x + i <= p_ptr->res_x)
		{
			j = 0;
			while (j < p_ptr->step && y - j >= 0)
			{
				my_mlx_pixel_put(p_ptr->pix_ptr, x + i, y - j, color);
				j++;
			}
			i++;
		}
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
			if (store > JEAN && (store < obj_dist || obj_dist == 0.0))
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
	y = p_ptr->res_y - 1;
	while (y >= 0 && !(x = 0))
	{
		ray.vec_v[0] = ray.unit_v[0] * (p_ptr->res_y / 2.0 - y);
		ray.vec_v[1] = ray.unit_v[1] * (p_ptr->res_y / 2.0 - y);
		ray.vec_v[2] = ray.unit_v[2] * (p_ptr->res_y / 2.0 - y);
		while (x < p_ptr->res_x)
		{
			ray.vec_u[0] = ray.unit_u[0] * (p_ptr->res_x / 2.0 * -1.0 + x);
			ray.vec_u[1] = ray.unit_u[1] * (p_ptr->res_x / 2.0 * -1.0 + x);
			ray.vec_u[2] = ray.unit_u[2] * (p_ptr->res_x / 2.0 * -1.0 + x);
			vec_addition(ray.direction, ray.vec_u, ray.vec_v, 3);
			vec_addition(ray.direction, ray.direction, ray.vec_w, 3);
			vec_normalize(ray.direction, 3);
			fill_window(p_ptr, set_ray_params(p_ptr, &ray, \
			set_closest(p_ptr, &ray)), x, y);
			x += p_ptr->step;
		}
		y -= p_ptr->step;
	}
}
