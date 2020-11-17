/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_errors_free.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:08:49 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 19:11:09 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../minirt.h"

void
	del_all_elem(t_object *object_ptr)
{
	t_object	*store;

	while (object_ptr)
	{
		store = object_ptr;
		object_ptr = object_ptr->next_object;
		free(store);
	}
}

void
	free_2d_array(char ***ptr)
{
	int i;

	i = 0;
	while ((*ptr)[i])
	{
		free((*ptr)[i]);
		i++;
	}
	free(*ptr);
	*ptr = NULL;
}

void
	free_all(t_param *param)
{
	if (param->line)
		free(param->line);
	if (param->line_split)
		free_2d_array(&(param->line_split));
	if (param->extra_split)
		free_2d_array(&(param->extra_split));
	if (param->object)
		del_all_elem(param->object);
}

void
	error_free(t_param *p_ptr, char *error_message)
{
	ft_putstr_fd(error_message, 1);
	ft_putchar_fd('\n', 1);
	if (p_ptr->line)
	{
		ft_putstr_fd("Error on line: ", 1);
		ft_putstr_fd(p_ptr->line, 1);
		ft_putchar_fd('\n', 1);
	}
	free_all(p_ptr);
	close(p_ptr->fd_rt);
	exit(1);
}
