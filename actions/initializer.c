/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:37:35 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 22:37:39 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	param_struct_init(t_param *param_ptr)
{
	param_ptr->save = 0;
	param_ptr->res_found = 0;
	param_ptr->amb_light_found = 0;
	param_ptr->line = NULL;
	param_ptr->line_split = NULL;
	param_ptr->object = NULL;
	param_ptr->extra_split = NULL;
	param_ptr->step = STEP;
	param_ptr->selected_obj = NULL;
}

void
	init_func_arr(t_args_func *func_arr)
{
	func_arr[sphere] = sphere_intersect;
	func_arr[plane] = plane_intersect;
	func_arr[square] = square_intersect;
	func_arr[triangle] = triangle_intersect;
	func_arr[cylinder] = cylinder_intersect;
}

int
	check_open_file(int argc, char **argv, t_param *p_ptr)
{
	param_struct_init(p_ptr);
	if (argc != 2)
	{
		if (argc == 3 && !(ft_strcmp(argv[2], SAVE_FLAG)))
			p_ptr->save = 1;
		else
		{
			ft_putstr_fd("Incorrect number of arguments or wrong flag", 1);
			return (0);
		}
	}
	if (!check_file_extansion(argv[1], FILE_EXTANSION))
	{
		ft_putstr_fd("Incorrect file extansion", 1);
		return (0);
	}
	if (!(p_ptr->fd_rt = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Could not open the file, please verify it exists\n", 1);
		return (0);
	}
	parse_params(p_ptr);
	return (1);
}
