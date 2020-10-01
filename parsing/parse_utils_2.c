/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_utils_2.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:13:30 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 19:04:45 by jmaydew		  ###	########.fr		  */
/*																			  */
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

float
	atoitof(t_param *param_ptr, char *s)
{
	int result;
	int i;
	int sign;

	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		sign = sign * -1;
		/* i++ here to save lines */
		s++;
	}
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.' && ft_isdigit(s[i + 1]) && s[i + 2] == '\0')
	{
		result = ft_atoi(s);
		result = result * 10 + s[i + 1] - '0';
		return (((float)result) / 10 * sign);
	}
	if (s[i] == '\0')
		return ((float)(result = ft_atoi(s) * sign));
	error_free(param_ptr, "Wrong format of floating point value");
	return (0.0f);
}

int
	get_rgb(t_param *param_ptr, char *s)
{
	int		i;
	int		store;
	int		rgb;

	if (!(param_ptr->extra_split = ft_split(s, ',')))
		error_free(param_ptr, "Split error in get_rgb function");
	if (array_size(param_ptr->extra_split) != 3)
		error_free(param_ptr, "Incorrect number of RGB parameters");
	rgb = 0;
	i = 0;
	while (param_ptr->extra_split[i])
	{
		if (!(ft_isnumber(param_ptr->extra_split[i])))
			error_free(param_ptr, "Incorrect entries in rgb");
		else
		{
			store = ft_atoi(param_ptr->extra_split[i]);
			if (store >= 0 && store <= 255 && ++i)
				rgb = (rgb << 8) + store;
			else
				error_free(param_ptr, "RGB value out of 0-255 range");
		}
	}
	free_2d_array(&param_ptr->extra_split);
	return (rgb);
}

void
	get_coord(char *s, float arr[], t_param *param_ptr, int size)
{
	int i;

	if (!(param_ptr->extra_split = ft_split(s, ',')))
		error_free(param_ptr, "Split error in 'get_coord' function");
	if (array_size(param_ptr->extra_split) != size)
		error_free(param_ptr, "Incorrect number of coordinates parameters");
	i = 0;
	while (i < size)
	{
		arr[i] = atoitof(param_ptr, param_ptr->extra_split[i]);
		i++;
	}
	free_2d_array(&param_ptr->extra_split);
}
