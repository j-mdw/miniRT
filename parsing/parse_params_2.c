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

#include "minirt.h"

void
	parse_resolution(t_param *param_ptr)
{		
	printf("R found\n"); /* TBR */
	if (param_ptr->res_found)
		error_free(param_ptr, "Resolution provided multiple times");
	else
		param_ptr->res_found = 1;
	if (array_size(param_ptr->line_split) != 3)
		error_free(param_ptr, "Incorrect number of arguments for Resolution");
	else
	{
		if (ft_isnumber(param_ptr->line_split[1]))
			param_ptr->res_x = ft_atoi(param_ptr->line_split[1]);
		else
			error_free(param_ptr, "Incorrect 'x' resolution value");
		if (ft_isnumber(param_ptr->line_split[2]))
			param_ptr->res_y = ft_atoi(param_ptr->line_split[2]);
		else
			error_free(param_ptr, "Incorrect 'y' resolution value");
	}
}

void
	parse_amb_light(t_param *param_ptr)
{
	printf("A found\n"); /* TBR */
	if (param_ptr->amb_light_found)
		error_free(param_ptr, "Ambiant light provided multiple times");
	else
		param_ptr->amb_light_found = 1;
	if (array_size(param_ptr->line_split) != 3)
		error_free(param_ptr, "Incorrect number of arguments for Ambiant light");
	else
	{
		param_ptr->light_ratio = atoitof(param_ptr, param_ptr->line_split[1]);
		if (param_ptr->light_ratio > 1.0 || param_ptr->light_ratio < 0.0)
			error_free(param_ptr, "Incorrect light ratio, make sure it is between 0.0 and 1.0");
		param_ptr->light_rgb = get_rgb(param_ptr, param_ptr->line_split[2]);
	}
}

void
	parse_camera(t_param *param_ptr)
{
	int			i;

	if (array_size(param_ptr->line_split) != 4)
		error_free(param_ptr, "Incorrect number of arguments for Camera");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = camera;
	get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
	get_coord(param_ptr->line_split[2], param_ptr->object->coord2, param_ptr, 3);
	i = 0;
	while (i < 3)
	{
		if (param_ptr->object->coord2[i] < -1.0 || param_ptr->object->coord2[i] > 1.0)
			error_free(param_ptr, "Orientation vector values out of [-1,1] range");  
		i++;
	}
	if ((ft_isnumber(param_ptr->line_split[3])))
	{
		param_ptr->object->fov = ft_atoi(param_ptr->line_split[3]);
		if (param_ptr->object->fov < 0 || param_ptr->object->fov >180)
			error_free(param_ptr, "Camera FOV not in range [0,180]");
	}
	else
		error_free(param_ptr, "Camera FOV not a number");
}

void
	parse_light(t_param *param_ptr)
{
	if (array_size(param_ptr->line_split) != 4)
		error_free(param_ptr, "Incorrect number of arguments for Light");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = light;
	get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
	param_ptr->object->brightness = atoitof(param_ptr, param_ptr->line_split[2]);
	if (param_ptr->object->brightness < 0.0 || param_ptr->object->brightness > 1.0)
		error_free(param_ptr, "Light brightness not in range [0.0,1.0]");
	param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[3]);
}

void
	parse_sphere(t_param *param_ptr)
{
	if (array_size(param_ptr->line_split) != 4)
		error_free(param_ptr, "Incorrect number of arguments for Sphere");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = sphere;
	get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
	param_ptr->object->diameter = atoitof(param_ptr, param_ptr->line_split[2]);
	param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[3]);
}
