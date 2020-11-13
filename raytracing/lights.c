#include "../minirt.h"

int
	convert_rgb_format(double *rgb_arr)
{
	int i;
	int rgb;

	i = 0;
	rgb = 0;
	while (i < 3)
	{
		rgb = (rgb << 8) + (unsigned int)(rgb_arr[i] * 255.0);
		i++;
	}
	return (rgb);
}

/*
** ray_ptr->n_normal: unit vector perpendicular to the surface
** ray_ptr->l_light_src: unit vector pointing towards the light source
** v_cam_eye: unit vector pointing towards the eye of the camera
**
** Lambertian Shading: Pix_color = k(d) * I * max(0, n.l)
**	 Where k(d) is the diffuse coefficient or the surface color
**	 where I is the intensity of the light source
**
** Specular reflexion: Blinn-Phong shading
** Pixel color = lambertian shading + k(s) * I * max(0,n.h)^p
**	 where p is the power of the shading: the greater it is, the faster the
**	 shininess will decrease
**	 where k(s) is the specular coefficient or specular color of the surface
**	 (in doubt, make it grey with equal red, green, blue)
**	 where h is (v + l) / ||v + l||
*/

double
	specular_reflexion(t_ray *ray_ptr, t_object *light_ptr)
{
	double	vec_h[3];
	double	spec_coeff;
    
    spec_coeff = 0.5;
	vec_copy(ray_ptr->direction, ray_ptr->v_cam_eye, 3);
	vec_scalarprod(ray_ptr->v_cam_eye, (-1.0 / \
	vec_magnit(ray_ptr->v_cam_eye, 3)), 3);
	vec_addition(vec_h, ray_ptr->v_cam_eye, ray_ptr->l_light_src, 3);
	vec_scalarprod(vec_h, (1 / vec_magnit(vec_h, 3)), 3);
	return (spec_coeff * light_ptr->brightness * \
	pow(max_d(0.0, dot_prod(ray_ptr->n_normal, vec_h, 3)), PHONG_EXPONENT));
}

int
	is_in_shadow(t_param *p_ptr, t_ray *ray_ptr)
{
	t_object	*surface;
	double		max_dist;
	double		store;
	t_ray		shadow_ray;

	max_dist = vec_magnit(ray_ptr->l_light_src, 3);
	surface = p_ptr->object;
	vec_copy(ray_ptr->vec_intersect, shadow_ray.origin, 3);
	vec_copy(ray_ptr->l_light_src, shadow_ray.direction, 3);
	vec_scalarprod(shadow_ray.direction, (1 / max_dist), 3);
	while (surface)
	{
		if (surface->obj_id < DIFF_SURFACE)
		{
			store = p_ptr->func_arr_ptr[surface->obj_id](&shadow_ray, surface);
			if (store > JEAN && pow(store, 2) < pow(max_dist, 2))
				return (1);
		}
		surface = surface->next_object;
	}
	return (0);
}

void
	get_color_2(t_param *p_ptr, t_ray *ray_ptr, t_object *light_ptr, \
	double *rgb)
{
	double	dot_l_n;
	int		i;

	vec_substract(ray_ptr->l_light_src, light_ptr->coord1, \
	ray_ptr->vec_intersect, 3);
	if (!is_in_shadow(p_ptr, ray_ptr))
	{
		vec_scalarprod(ray_ptr->l_light_src, (1 / \
		vec_magnit(ray_ptr->l_light_src, 3)), 3);
		dot_l_n = max_d(0.0, dot_prod(ray_ptr->n_normal, \
		ray_ptr->l_light_src, 3));
		i = 0;
		while (i < 3)
		{
			rgb[i] += p_ptr->closest_surface->rgb[i] * light_ptr->brightness *\
			 light_ptr->rgb[i] * dot_l_n;// + specular_reflexion(ray_ptr, light_ptr); //TBU: bcs specular reflexion is added, if light color is black, there is still reflexion
			i++;
		}
	}
}

int
	get_color(t_param *p_ptr, t_ray *ray_ptr)
{
	double		rgb[3];
	t_object	*light_ptr;
	int			i;

	i = 0;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	light_ptr = p_ptr->object;
	while (light_ptr)
	{
		if (light_ptr->obj_id == light)
			get_color_2(p_ptr, ray_ptr, light_ptr, rgb);
		light_ptr = light_ptr->next_object;
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] += p_ptr->light_ratio * p_ptr->light_rgb[i];
		if (rgb[i] > 1.0)
			rgb[i] = 1.0;
		i++;
	}
	return (convert_rgb_format(rgb));
}
