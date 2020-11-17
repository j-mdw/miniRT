/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:06:52 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 19:06:54 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int
	ft_isnumber(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

int
	array_size(char **arr_ptr)
{
	int i;

	i = 0;
	while (arr_ptr[i])
		i++;
	return (i);
}

double
	atoitod(t_param *p_ptr, char *s)
{
	int result;
	int i;
	int sign;

	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		sign = sign * -1;
		s++;
	}
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.' && ft_isdigit(s[i + 1]) && s[i + 2] == '\0')
	{
		result = minirt_atoi(s, p_ptr);
		result = result * 10 + s[i + 1] - '0';
		return (((double)result) / 10 * sign);
	}
	if (s[i] == '\0')
		return ((double)(result = minirt_atoi(s, p_ptr) * sign));
	error_free(p_ptr, "Wrong format of floating point value");
	return (0.0f);
}

void
	get_rgb(t_param *p_ptr, char *s, double *arr)
{
	int		i;
	double	store;

	if (!(p_ptr->extra_split = ft_split(s, ',')))
		error_free(p_ptr, "Split error in get_rgb function");
	if (array_size(p_ptr->extra_split) != 3)
		error_free(p_ptr, "Incorrect number of RGB parameters");
	i = 0;
	while (p_ptr->extra_split[i])
	{
		if (!(ft_isnumber(p_ptr->extra_split[i])))
			error_free(p_ptr, "Incorrect entries in rgb");
		else
		{
			store = atoitod(p_ptr, p_ptr->extra_split[i]);
			if (store >= 0.0 && store <= 255.0)
				arr[i++] = (store / 255.0);
			else
				error_free(p_ptr, "RGB value out of 0-255 range");
		}
	}
	free_2d_array(&p_ptr->extra_split);
}

void
	get_coord(char *s, double arr[], t_param *p_ptr, int size)
{
	int i;

	if (!(p_ptr->extra_split = ft_split(s, ',')))
		error_free(p_ptr, "Split error in 'get_coord' function");
	if (array_size(p_ptr->extra_split) != size)
		error_free(p_ptr, "Incorrect number of coordinates parameters");
	i = 0;
	while (i < size)
	{
		arr[i] = atoitod(p_ptr, p_ptr->extra_split[i]);
		i++;
	}
	free_2d_array(&p_ptr->extra_split);
}
