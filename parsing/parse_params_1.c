/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_params_1.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:13:07 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 19:46:15 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minirt.h"

static void
	get_id(t_param *p_ptr)
{
	if (!ft_strcmp(*p_ptr->line_split, "R"))
		parse_resolution(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "A"))
		parse_amb_light(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "c"))
		parse_camera(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "l"))
		parse_light(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "sp"))
		parse_sphere(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "pl"))
		parse_plane(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "sq"))
		parse_square(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "cy"))
		parse_cylinder(p_ptr);
	else if (!ft_strcmp(*p_ptr->line_split, "tr"))
		parse_triangle(p_ptr);
	else
		error_free(p_ptr, "Incorrect identifier (from Get_ID)");
}

int
	parse_params(t_param *p_ptr)
{
	int gnl;

	while ((gnl = get_next_line(p_ptr->fd, &p_ptr->line)) > 0)
	{
		printf("Line: %s\n", p_ptr->line);
		replace_char(p_ptr->line, '\t', ' ');
		if (p_ptr->line[0]) /* Checking if line is not '\0' which corresponds to an empty line in the file */
		{
			if (!(p_ptr->line_split = ft_split(p_ptr->line, ' ')))
				error_free(p_ptr, "Split Error");
			if ((p_ptr->line_split[0])) /* Checking if *line_split != NULL - this would happen if line was only white spaces */
				get_id(p_ptr);
		}
		if (p_ptr->line_split)
			free_2d_array(&p_ptr->line_split);
		free(p_ptr->line);
	}
	printf("GNL RETURN: %d\n", gnl);
	if (gnl < 0)
		error_free(p_ptr, "Could not read file");
	if (!(p_ptr->res_found) || !(p_ptr->amb_light_found))
		error_free(p_ptr, "Missing parameter Resolution or Ambiant Light");
	return (1);
}
