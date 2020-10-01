/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:13:07 by jmaydew           #+#    #+#             */
/*   Updated: 2020/10/01 19:44:18 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
    parse_plane(t_param *param_ptr)
{
    int i;
	if (array_size(param_ptr->line_split) != 4)
		error_free(param_ptr, "Incorrect number of arguments for Plane");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = plane;
    get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
    get_coord(param_ptr->line_split[2], param_ptr->object->coord2, param_ptr, 3);
    i = 0;
    while (param_ptr->object->coord2[i] >= -1.0 && param_ptr->object->coord2[i] <= 1.0 && i < 3)
        i++;
    if (i != 3)
        error_free(param_ptr, "Orientation vector inputs not in range [-1,1]");
    param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[3]);
}

void
    parse_square(t_param *param_ptr)
{
    int i;
	if (array_size(param_ptr->line_split) != 5)
		error_free(param_ptr, "Incorrect number of arguments for Square");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = square;
    get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
    get_coord(param_ptr->line_split[2], param_ptr->object->coord2, param_ptr, 3);
    i = 0;
    while (param_ptr->object->coord2[i] >= -1.0 && param_ptr->object->coord2[i] <= 1.0 && i < 3)
        i++;
    if (i != 3)
        error_free(param_ptr, "Orientation vector inputs not in range [-1,1]");
    param_ptr->object->height = atoitof(param_ptr, param_ptr->line_split[3]);
    param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[4]);
}

void
    parse_cylinder(t_param *param_ptr)
{
    int i;
	if (array_size(param_ptr->line_split) != 6)
		error_free(param_ptr, "Incorrect number of arguments for Cylinder");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = cylinder;
    get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
    get_coord(param_ptr->line_split[2], param_ptr->object->coord2, param_ptr, 3);
    i = 0;
    while (param_ptr->object->coord2[i] >= -1.0 && param_ptr->object->coord2[i] <= 1.0 && i < 3)
        i++;
    if (i != 3)
        error_free(param_ptr, "Orientation vector inputs not in range [-1,1]");
    param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[3]);
    param_ptr->object->diameter = atoitof(param_ptr, param_ptr->line_split[4]);
    param_ptr->object->height = atoitof(param_ptr, param_ptr->line_split[5]);
}

void
    parse_triangle(t_param *param_ptr)
{
	if (array_size(param_ptr->line_split) != 5)
		error_free(param_ptr, "Incorrect number of arguments for Triangle");
	add_new_elem_front(param_ptr);
	param_ptr->object->obj_id = triangle;
    get_coord(param_ptr->line_split[1], param_ptr->object->coord1, param_ptr, 3);
    get_coord(param_ptr->line_split[2], param_ptr->object->coord2, param_ptr, 3);
    get_coord(param_ptr->line_split[3], param_ptr->object->coord3, param_ptr, 3);
    param_ptr->object->rgb = get_rgb(param_ptr, param_ptr->line_split[4]);
}
