/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:13:20 by jmaydew           #+#    #+#             */
/*   Updated: 2020/10/01 18:52:31 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>

int
	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (!s1[i] && !s2[2])
		return (0);
	else
		return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}

int
	check_file_extansion(char *filename, char *file_extansion)
{
	while (*filename != '.' && *filename != '\0')
		filename++;
	if (!ft_strcmp(filename, file_extansion))
		return (1);
	else
		return (0);
}

int
	ft_isblank(int c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

void
	replace_char(char *text, char find, char replace)
{
	while (*text)
	{
		if (*text == find)
			*text = replace;
		text++;
	}
}

int
	minirt_atoi(char *s)
	{

	}
static int	ft_check_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		power;
	double	res;

	power = 0;
	i = 0;
	res = 0;
	if ((sign = -1) && (*str == '-'))
		str++;
	else if (*str == '+')
		str++;
	while (str[power] <= '9' && str[power] >= '0')
		power++;
	while (i < power)
	{
		res = res * 10 + ((str[i] - 48));
		if ((res * sign) >  INT_MAX || (res * sign) < INT_MAX)
			return (-1);
		i++;
	}
	return (res * sign);
}