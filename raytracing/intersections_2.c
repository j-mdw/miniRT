#include "../minirt.h"

static int
	tri_helper(t_object *tri_ptr, double *tri_n, double *intersec)
{
	double	tmp_vec1[3];
	double	tmp_vec2[3];
	double	tmp_vec3[3];
	int		sum_check;

	vec_substract(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
	vec_substract(tmp_vec2, intersec, tri_ptr->coord1, 3);
	cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
	sum_check = 0;
	if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
		sum_check += 1;
	vec_substract(tmp_vec1, tri_ptr->coord3, tri_ptr->coord2, 3);
	vec_substract(tmp_vec2, intersec, tri_ptr->coord2, 3);
	cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
	if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
		sum_check += 1;
	vec_substract(tmp_vec1, tri_ptr->coord1, tri_ptr->coord3, 3);
	vec_substract(tmp_vec2, intersec, tri_ptr->coord3, 3);
	cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
	if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
		sum_check += 1;
	return (sum_check);
}

double
	triangle_intersect(t_ray *ray_ptr, t_object *tri_ptr)
{
	double	tri_n[3];
	double	plane_dist;
	double	tmp_vec1[3];
	double	point_inter[3];
	int		sum_check;

	vec_substract(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
	vec_substract(tri_n, tri_ptr->coord3, tri_ptr->coord2, 3);
	cross_product(tri_n, tmp_vec1, tri_n);
	vec_normalize(tri_n, 3);
	if (dot_prod(tri_n, ray_ptr->direction, 3) > 0.0)
		vec_scalarprod(tri_n, -1.0, 3);
	if ((plane_dist = get_plane_intersec(ray_ptr, \
	tri_ptr->coord1, tri_n)) < 0.0)
		return (0.0);
	vec_copy(ray_ptr->direction, point_inter, 3);
	vec_scalarprod(point_inter, plane_dist, 3);
	vec_addition(point_inter, point_inter, ray_ptr->origin, 3);
	sum_check = tri_helper(tri_ptr, tri_n, point_inter);
	if (sum_check == 3 || sum_check == 0)
		return (plane_dist);
	return (0.0);
}

/*
**	Parameters:
**	- Ro : ray origin
**	- Rd : ray direction
**	- Co : cylinder origin
**	- Cn : cylinder normal
**	- r  : Ray
**
**	Formula: (P - Co - (Cn . (P - Co)*Cn))^2 - r^2 = 0
**	Where P is the point on the cylinder.
**   Replace P by Ro + Rd*t and simplify to get quad terms
**	a = (Rd - (Rd . Cn)*Cn)^2
**	b = 2 * ((Rd - (Rd . Cn)*Cn) . ((Ro - Co) - ((Ro - Co).Cn)*Cn))
**	c = ((Ro - Co) - ((Ro - Co).Cn)*Cn)^2 - r^2
*/

double
	cylinder_intersect(t_ray *ray_ptr, t_object *cy_ptr)
{
	t_quadratic q_param;
	double		vec1[3];
	double		vec2[3];
	double		co_to_ro[3];

	vec_copy(cy_ptr->coord2, vec1, 3);
	vec_scalarprod(vec1, dot_prod(ray_ptr->direction, cy_ptr->coord2, 3), 3);
	vec_substract(vec1, ray_ptr->direction, vec1, 3);
	q_param.a = dot_prod(vec1, vec1, 3);
	vec_substract(co_to_ro, ray_ptr->origin, cy_ptr->coord1, 3);
	vec_copy(cy_ptr->coord2, vec2, 3);
	vec_scalarprod(vec2, dot_prod(co_to_ro, vec2, 3), 3);
	vec_substract(vec2, co_to_ro, vec2, 3);
	q_param.b = 2 * dot_prod(vec1, vec2, 3);
	q_param.c = dot_prod(vec2, vec2, 3) - pow(cy_ptr->diameter / 2, 2);
	q_param.discrim = pow(q_param.b, 2) - 4 * q_param.a * q_param.c;
	if (q_param.discrim < 0.0)
		return (0.0);
	else if (q_param.discrim == 0)
		return (-q_param.b / (2 * q_param.a));
	q_param.solut_1 = (-q_param.b - sqrt(q_param.discrim)) / (2 * q_param.a);
	q_param.solut_2 = (-q_param.b + sqrt(q_param.discrim)) / (2 * q_param.a);
	if (q_param.solut_1 > 0.0 && q_param.solut_1 < q_param.solut_2)
		return (q_param.solut_1);
	return (q_param.solut_2);
}
