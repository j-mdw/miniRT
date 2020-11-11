#include "../minirt.h"

double
	sphere_intersect(t_ray *ray_ptr, t_object *sphere)
{
	t_quadratic q_param;
	double		temp_vec[3];

	q_param.a = dot_prod(ray_ptr->direction, ray_ptr->direction, 3);
	vec_substract(temp_vec, ray_ptr->origin, sphere->coord1, 3);
	q_param.b = 2.0 * dot_prod(ray_ptr->direction, temp_vec, 3);
	q_param.c = dot_prod(temp_vec, temp_vec, 3) - \
	pow((sphere->diameter / 2.0), 2);
	q_param.discrim = pow(q_param.b, 2) - 4 * q_param.a * q_param.c;
	if (q_param.discrim < 0.0)
		return (-1.0);
	else if (q_param.discrim == 0)
		return (-q_param.b / (2 * q_param.a));
	q_param.solut_1 = (-q_param.b - sqrt(q_param.discrim)) / (2 * q_param.a);
	q_param.solut_2 = (-q_param.b + sqrt(q_param.discrim)) / (2 * q_param.a);
	if (q_param.solut_1 > 0.0 && q_param.solut_1 < q_param.solut_2)
		return (q_param.solut_1);
	return (q_param.solut_2);
}

double
	get_plane_intersec(t_ray *ray_ptr, double *plane_origin, double *plane_n)
{
	double	intersect;
	double	tmp_val;
	double	tmp_vec[3];

	if ((tmp_val = dot_prod(ray_ptr->direction, plane_n, 3)) == 0.0)
		return (0.0);
	vec_substract(tmp_vec, plane_origin, ray_ptr->origin, 3);
	intersect = dot_prod(tmp_vec, plane_n, 3) / tmp_val;
	return (intersect);
}

double
	plane_intersect(t_ray *ray_ptr, t_object *plane_ptr)
{
	return (get_plane_intersec(ray_ptr, plane_ptr->coord1, plane_ptr->coord2));
}

static double
	sq_helper(t_object *sq_ptr, double *vec)
{
	t_ray	pov_plan;
	double	side_dist;

	set_pov_plan(sq_ptr->coord2, &pov_plan);
	if ((side_dist = fabs(dot_prod(pov_plan.vec_u, vec, 3))) \
	<= ((cos(45.0 / 180.0 * M_PI))))
		side_dist = fabs(dot_prod(pov_plan.vec_v, vec, 3));
	side_dist = (sq_ptr->height / 2) / side_dist;
	return (side_dist);
}

double
	square_intersect(t_ray *ray_ptr, t_object *sq_ptr)
{
	double	vec[3];
	double	plane_inter;
	double	tmp_val;
	double	length;

	if ((plane_inter = get_plane_intersec(ray_ptr, \
	sq_ptr->coord1, sq_ptr->coord2)) > JEAN)
	{
		vec_copy(ray_ptr->direction, vec, 3);
		vec_scalarprod(vec, plane_inter, 3);
		vec_addition(vec, vec, ray_ptr->origin, 3);
		vec_substract(vec, vec, sq_ptr->coord1, 3);
		if ((length = vec_magnit(vec, 3)) > \
		sqrt(pow(sq_ptr->height / 2, 2) * 2))
			return (0.0);
		if (length == 0.0)
			return (plane_inter);
		vec_normalize(vec, 3);
		tmp_val = sq_helper(sq_ptr, vec);
		if (length < tmp_val)
			return (plane_inter);
	}
	return (0.0);
}
