/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_params.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:13:07 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 19:13:49 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../minirt.h"

void
	parse_resolution(t_param *p_ptr)
{
	if (p_ptr->res_found)
		error_free(p_ptr, "Resolution provided multiple times");
	else
		p_ptr->res_found = 1;
	if (array_size(p_ptr->line_split) != 3)
		error_free(p_ptr, "Incorrect number of arguments for Resolution");
	else
	{
		if (ft_isnumber(p_ptr->line_split[1]))
			p_ptr->res_x = minirt_atoi(p_ptr->line_split[1], p_ptr);
		else
			error_free(p_ptr, "Incorrect 'x' resolution value");
		if (ft_isnumber(p_ptr->line_split[2]))
			p_ptr->res_y = minirt_atoi(p_ptr->line_split[2], p_ptr);
		else
			error_free(p_ptr, "Incorrect 'y' resolution value");
	}
}

void
	parse_amb_light(t_param *p_ptr)
{
	if (p_ptr->amb_light_found)
		error_free(p_ptr, "Ambiant light provided multiple times");
	else
		p_ptr->amb_light_found = 1;
	if (array_size(p_ptr->line_split) != 3)
		error_free(p_ptr, "Incorrect nb of arg for Ambiant light");
	else
	{
		p_ptr->light_ratio = atoitod(p_ptr, p_ptr->line_split[1]);
		if (p_ptr->light_ratio > 1.0 || p_ptr->light_ratio < 0.0)
			error_free(p_ptr, "Light ratio not in  [0.0,1.0]");
		get_rgb(p_ptr, p_ptr->line_split[2], p_ptr->light_rgb);
	}
	vec_scalarprod(p_ptr->light_rgb, p_ptr->light_ratio, 3);
}

void
	parse_camera(t_param *p_ptr)
{
	if (array_size(p_ptr->line_split) != 4)
		error_free(p_ptr, "Incorrect nb of arguments for Camera");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = camera;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	get_coord(p_ptr->line_split[2], p_ptr->object->coord2, p_ptr, 3);
	if ((p_ptr->object->coord2[0] < -1.0 || p_ptr->object->coord2[0] > 1.0) \
	|| (p_ptr->object->coord2[1] < -1.0 || p_ptr->object->coord2[1] > 1.0) \
	|| (p_ptr->object->coord2[2] < -1.0 || p_ptr->object->coord2[2] > 1.0))
		error_free(p_ptr, "Orientation vector out of [-1,1] range");
	if (p_ptr->object->coord2[0] == 0.0 && p_ptr->object->coord2[1] == 0.0 \
	&& p_ptr->object->coord2[2] == 0.0)
		error_free(p_ptr, "At least 1 coord. of cam. orient vec. must be != 0");
	vec_normalize(p_ptr->object->coord2, 3);
	if ((ft_isnumber(p_ptr->line_split[3])))
	{
		p_ptr->object->fov = minirt_atoi(p_ptr->line_split[3], p_ptr);
		if (p_ptr->object->fov <= 0 || p_ptr->object->fov >= 180)
			error_free(p_ptr, "Camera FOV not in range ]0,180[");
	}
	else
		error_free(p_ptr, "Camera FOV not a number");
	p_ptr->cam_found += 1;
}

void
	parse_light(t_param *p_ptr)
{
	if (array_size(p_ptr->line_split) != 4)
		error_free(p_ptr, "Incorrect nb of arguments for Light");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = light;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	p_ptr->object->brightness = atoitod(p_ptr, p_ptr->line_split[2]);
	if (p_ptr->object->brightness < 0.0 || p_ptr->object->brightness > 1.0)
		error_free(p_ptr, "Light brightness not in [0.0,1.0]");
	get_rgb(p_ptr, p_ptr->line_split[3], p_ptr->object->rgb);
}

void
	parse_sphere(t_param *p_ptr)
{
	if (array_size(p_ptr->line_split) != 4)
		error_free(p_ptr, "Incorrect nb of arguments for Sphere");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = sphere;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	p_ptr->object->diameter = atoitod(p_ptr, p_ptr->line_split[2]);
	if (p_ptr->object->diameter <= 0)
		error_free(p_ptr, "Diameter must be greater than 0");
	get_rgb(p_ptr, p_ptr->line_split[3], p_ptr->object->rgb);
}
