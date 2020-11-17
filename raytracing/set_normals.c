/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:08:47 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:08:48 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void
	set_normal_2(t_object *surface, t_ray *ray_ptr)
{
	double	tmp_vec1[3];
	double	tmp_vec2[3];

	if (surface->obj_id == triangle)
	{
		vec_substract(tmp_vec1, surface->coord2, surface->coord1, 3);
		vec_substract(tmp_vec2, surface->coord3, surface->coord2, 3);
		cross_product(ray_ptr->n_normal, tmp_vec1, tmp_vec2);
		vec_normalize(ray_ptr->n_normal, 3);
		if (dot_prod(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
			vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
	}
	if (surface->obj_id == cylinder)
	{
		vec_substract(tmp_vec1, ray_ptr->vec_intersect, surface->coord1, 3);
		vec_copy(surface->coord2, tmp_vec2, 3);
		vec_scalarprod(tmp_vec2, dot_prod(tmp_vec1, tmp_vec2, 3), 3);
		vec_substract(ray_ptr->n_normal, tmp_vec1, tmp_vec2, 3);
		vec_normalize(ray_ptr->n_normal, 3);
		if (dot_prod(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
			vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
	}
}

void
	set_normal(t_object *surface, t_ray *ray_ptr)
{
	if (surface->obj_id == sphere)
	{
		vec_substract(ray_ptr->n_normal, ray_ptr->vec_intersect, \
		surface->coord1, 3);
		vec_normalize(ray_ptr->n_normal, 3);
		if (dot_prod(ray_ptr->n_normal, ray_ptr->direction, 3) > 0.0)
			vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
	}
	if (surface->obj_id == plane || surface->obj_id == square)
	{
		vec_copy(surface->coord2, ray_ptr->n_normal, 3);
		if (dot_prod(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
			vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
	}
	if (surface->obj_id == triangle || surface->obj_id == cylinder)
		set_normal_2(surface, ray_ptr);
}
