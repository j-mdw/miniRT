/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_utils_3.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:13:39 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 19:26:09 by jmaydew		  ###	########.fr		  */
/*																			  */
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
