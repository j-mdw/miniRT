/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:13:07 by jmaydew           #+#    #+#             */
/*   Updated: 2020/10/01 19:46:15 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
    get_id(t_param *param_ptr)
{ 
    if (!ft_strcmp(*param_ptr->line_split, "R"))
        parse_resolution(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "A"))
        parse_amb_light(param_ptr);
	else if (!ft_strcmp(*param_ptr->line_split, "c"))
	    parse_camera(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "l"))
        parse_light(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "sp"))
        parse_sphere(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "pl"))
        parse_plane(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "sq"))
        parse_square(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "cy"))
        parse_cylinder(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "tr"))
        parse_triangle(param_ptr);
    else
        error_free(param_ptr, "Incorrect identifier (from Get_ID)");
}

int
    parse_params(t_param *param_ptr, int fd)
{
    int gnl;

    while ((gnl = get_next_line(fd, &param_ptr->line)) > 0)  
    {
        printf("Line: %s\n", param_ptr->line);
        replace_char(param_ptr->line, '\t', ' ');
        if (param_ptr->line[0]) /* Checking if line is not '\0' which corresponds to an empty line in the file */
        {
            if (!(param_ptr->line_split = ft_split(param_ptr->line, ' ')))
                error_free(param_ptr, "Split Error");
            if ((param_ptr->line_split[0])) /* Checking if *line_split != NULL - this would happen if line was only white spaces */
                get_id(param_ptr);
        }
        if (param_ptr->line_split)
            free_2d_array(&param_ptr->line_split);
        free(param_ptr->line);
    }
    printf("GNL RETURN: %d\n", gnl);
    if (gnl < 0)
        error_free(param_ptr, "Could not read file");
    if (!(param_ptr->res_found) || !(param_ptr->amb_light_found))
        error_free(param_ptr, "Missing necessary parameter Resolution or Ambiant Light");
    return (1);
}
