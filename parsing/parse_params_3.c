/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:06:16 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:06:18 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	parse_plane(t_param *p_ptr)
{
	int i;

	if (array_size(p_ptr->line_split) != 4)
		error_free(p_ptr, "Incorrect number of arguments for Plane");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = plane;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	get_coord(p_ptr->line_split[2], p_ptr->object->coord2, p_ptr, 3);
	i = 0;
	while (p_ptr->object->coord2[i] >= -1.0 \
			&& p_ptr->object->coord2[i] <= 1.0 && i < 3)
		i++;
	if (i != 3)
		error_free(p_ptr, "Orientation vector inputs not in range [-1,1]");
	vec_normalize(p_ptr->object->coord2, 3);
	get_rgb(p_ptr, p_ptr->line_split[3], p_ptr->object->rgb);
	set_vec_up(p_ptr->object->coord3);
}

void
	parse_square(t_param *p_ptr)
{
	int i;

	if (array_size(p_ptr->line_split) != 5)
		error_free(p_ptr, "Incorrect number of arguments for Square");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = square;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	get_coord(p_ptr->line_split[2], p_ptr->object->coord2, p_ptr, 3);
	i = 0;
	while (p_ptr->object->coord2[i] >= -1.0 && \
			p_ptr->object->coord2[i] <= 1.0 && i < 3)
		i++;
	if (i != 3)
		error_free(p_ptr, "Orientation vector inputs not in range [-1,1]");
	vec_normalize(p_ptr->object->coord2, 3);
	if ((p_ptr->object->height = atoitod(p_ptr, p_ptr->line_split[3])) <= 0)
		error_free(p_ptr, "Square height must be greater than 0");
	get_rgb(p_ptr, p_ptr->line_split[4], p_ptr->object->rgb);
	set_vec_up(p_ptr->object->coord3);
}

void
	parse_cylinder(t_param *p_ptr)
{
	int i;

	if (array_size(p_ptr->line_split) != 6)
		error_free(p_ptr, "Incorrect number of arguments for Cylinder");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = cylinder;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	get_coord(p_ptr->line_split[2], p_ptr->object->coord2, p_ptr, 3);
	i = 0;
	while (p_ptr->object->coord2[i] >= -1.0 && \
			p_ptr->object->coord2[i] <= 1.0 && i < 3)
		i++;
	if (i != 3)
		error_free(p_ptr, "Orientation vector inputs not in range [-1,1]");
	vec_normalize(p_ptr->object->coord2, 3);
	p_ptr->object->diameter = atoitod(p_ptr, p_ptr->line_split[3]);
	p_ptr->object->height = atoitod(p_ptr, p_ptr->line_split[4]);
	if (p_ptr->object->height <= 0 || p_ptr->object->diameter <= 0)
		error_free(p_ptr, "Square height/diameter must be greater than 0");
	get_rgb(p_ptr, p_ptr->line_split[5], p_ptr->object->rgb);
	set_vec_up(p_ptr->object->coord3);
}

void
	parse_triangle(t_param *p_ptr)
{
	if (array_size(p_ptr->line_split) != 5)
		error_free(p_ptr, "Incorrect number of arguments for Triangle");
	add_new_elem_front(p_ptr);
	p_ptr->object->obj_id = triangle;
	get_coord(p_ptr->line_split[1], p_ptr->object->coord1, p_ptr, 3);
	get_coord(p_ptr->line_split[2], p_ptr->object->coord2, p_ptr, 3);
	get_coord(p_ptr->line_split[3], p_ptr->object->coord3, p_ptr, 3);
	get_rgb(p_ptr, p_ptr->line_split[4], p_ptr->object->rgb);
}
