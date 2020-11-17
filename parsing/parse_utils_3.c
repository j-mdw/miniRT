/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:07:05 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:07:06 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	add_new_elem_front(t_param *param_ptr)
{
	t_object *new_obj;

	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		error_free(param_ptr, "New element malloc error");
	new_obj->next_object = param_ptr->object;
	param_ptr->object = new_obj;
}

void
	set_vec_up(double *vec)
{
	vec[0] = 0;
	vec[1] = 1;
	vec[2] = 0;
}

void
	resize_res(t_param *p_ptr)
{
	int	display_x;
	int	display_y;

	mlx_get_screen_size(p_ptr->mlx_ptr, &display_x, &display_y);
	if (display_x < p_ptr->res_x)
		p_ptr->res_x = display_x;
	if (display_y < p_ptr->res_y)
		p_ptr->res_y = display_y;
}
