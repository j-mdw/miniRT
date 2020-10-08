/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:12:03 by jmaydew           #+#    #+#             */
/*   Updated: 2020/10/01 18:30:15 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

typedef enum	e_param_id {
	camera,
	light,
	sphere,
	plane,
	square,
	cylinder,
	triangle,
}				t_param_id;

typedef struct	s_object {
	int				obj_id;
	double			coord1[3];
	double			coord2[3];
	double			coord3[3];
	double			diameter;
	double			brightness;
	double			height;
	int				rgb;
	int				fov;
	struct s_object	*next_object;
}				t_object;

typedef	struct	s_param {
	int			res_found;
	int			amb_light_found;
	int			res_x;
	int			res_y;
	double		light_ratio;
	int			light_rgb;
	int			save;
	char		*line;
	char		**line_split;
	char		**extra_split;
	t_param_id	*elem_id;
	t_object	*object;
}				t_param;

typedef	struct	s_ray {
	double	origin[3];
	double	direction[3];
}				t_ray;


int				ft_strcmp(const char *s1, const char *s2);
int				check_file_extansion(char *filename, char *file_extansion);
int				ft_isblank(int c);
void			replace_char(char *text, char find, char replace);
int				parse_params(t_param *p_ptr, int fd);
void			error_free(t_param *param, char *error_message);
void			error_free(t_param *param, char *error_message);
void			free_all(t_param *param);
int				ft_isnumber(char *s);
int				array_size(char **arr_ptr);
double			atoitod(t_param *p_ptr, char *s);
int				get_rgb(t_param *p_ptr, char *s);
void			add_new_elem_front(t_param *p_ptr);
void			free_2d_array(char ***ptr);
void			get_coord(char *s, double arr[], t_param *p_ptr, int size);
void			parse_resolution(t_param *p_ptr);
void			parse_amb_light(t_param *p_ptr);
void			parse_camera(t_param *p_ptr);
void			parse_light(t_param *p_ptr);
void			parse_sphere(t_param *p_ptr);
void			parse_plane(t_param *p_ptr);
void			parse_square(t_param *p_ptr);
void			parse_cylinder(t_param *p_ptr);
void			parse_triangle(t_param *p_ptr);
int				minirt_atoi(char *s, t_param *p_ptr);
int				ray_trace(t_param *p_ptr);
#endif
