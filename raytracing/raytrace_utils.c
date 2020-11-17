/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:08:34 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:32:05 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object
	*get_object(t_object *obj_ptr, int obj_id)
{
	while (obj_ptr->obj_id != obj_id && obj_ptr->next_object != NULL)
		obj_ptr = obj_ptr->next_object;
	if (obj_ptr->obj_id == obj_id)
		return (obj_ptr);
	return (NULL);
}

t_object
	*get_next_object(t_param *p_ptr, t_object *current_obj, int obj_id)
{
	t_object *tmp_obj;
	t_object *store;

	store = current_obj;
	if (current_obj->next_object)
		tmp_obj = current_obj->next_object;
	else
		tmp_obj = p_ptr->object;
	while (tmp_obj->obj_id != obj_id)
	{
		if (!tmp_obj->next_object)
			tmp_obj = p_ptr->object;
		else if (tmp_obj == store)
			return (NULL);
		else
			tmp_obj = tmp_obj->next_object;
	}
	if (tmp_obj != store)
		return (tmp_obj);
	return (NULL);
}

void
	set_pov_plan(double *orient_vec, double *up_vec, t_ray *ray_ptr)
{
	vec_copy(up_vec, ray_ptr->vec_v, 3);
	vec_copy(orient_vec, ray_ptr->vec_w, 3);
	if (fabs(dot_prod(orient_vec, up_vec, 3)) == 1.0)
	{
		ray_ptr->vec_w[0] += 0.001;
		vec_normalize(ray_ptr->vec_w, 3);
	}
	cross_product(ray_ptr->vec_u, ray_ptr->vec_v, ray_ptr->vec_w);
	cross_product(ray_ptr->vec_v, ray_ptr->vec_w, ray_ptr->vec_u);
	vec_normalize(ray_ptr->vec_u, 3);
	vec_normalize(ray_ptr->vec_v, 3);
}

void
	set_camera_plan(t_param *p_ptr, t_ray *ray_ptr)
{
	ray_ptr->screen_dist = (((double)p_ptr->res_x) / 2.0) / \
	tan(((double)p_ptr->current_camera->fov) / (2.0 * 180.0) * M_PI);
	vec_copy(p_ptr->current_camera->coord1, ray_ptr->origin, 3);
	set_pov_plan(p_ptr->current_camera->coord2, \
	p_ptr->current_camera->coord3, ray_ptr);
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
