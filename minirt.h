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

#ifndef M_PI
# define M_PI acos(-1.0)
#endif

#define PHONG_EXPONENT 100.0
#define	DIFF_SURFACE 5
#define	JEAN 0.000001
#define	STEP 16

# include "../libft/libft.h"
# include "gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
#include <limits.h>
#include <stdio.h>

typedef enum	e_param_id {
	sphere,
	plane,
	square,
	cylinder,
	triangle,
	camera,
	light,
}				t_param_id;

typedef struct	s_object {
	int				obj_id;
	double			coord1[3];
	double			coord2[3];
	double			coord3[3];
	double			diameter;
	double			brightness;
	double			height;
	double			rgb[3];
	int				fov;
	struct s_object	*next_object;
}				t_object;

typedef	struct	s_ray {
	double		origin[3];
	double		direction[3];
	double		vec_u[3];
	double		vec_v[3];
	double		vec_w[3];
	double		unit_u[3];
	double		unit_v[3];
	double		screen_dist;
	double		vec_intersect[3];
	double		v_cam_eye[3];
	double		n_normal[3];
	double		l_light_src[3];
	double		tmp_vec[3];
}				t_ray;

typedef struct s_pix_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_pix_data;

typedef struct s_quadratic {
	double      discrim;
    double      a;
    double      b;
    double      c;
    double      solut_1;
    double      solut_2;
} t_quadratic;

typedef double (*t_args_func)(t_ray *ray_ptr, t_object *object);

typedef	struct	s_param {
	int			step;
	int			fd;
	int			res_found;
	int			amb_light_found;
	int			cam_found;
	int			res_x;
	int			res_y;
	double		light_ratio;
	double		light_rgb[3];
	int			save;
	char		*line;
	char		**line_split;
	char		**extra_split;
	t_param_id	*elem_id;
	t_object	*object;
	t_object	*current_camera;
	t_pix_data	*pix_ptr;
	t_args_func	*func_arr_ptr;
	void		*mlx_ptr;
	void		*mlx_win_ptr;
}				t_param;

int				ft_strcmp(const char *s1, const char *s2);
int				check_file_extansion(char *filename, char *file_extansion);
int				ft_isblank(int c);
void			replace_char(char *text, char find, char replace);
int				parse_params(t_param *p_ptr);
void			error_free(t_param *param, char *error_message);
void			error_free(t_param *param, char *error_message);
void			free_all(t_param *param);
int				ft_isnumber(char *s);
int				array_size(char **arr_ptr);
double			atoitod(t_param *p_ptr, char *s);
void			get_rgb(t_param *p_ptr, char *s, double *arr);
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
void			my_mlx_pixel_put(t_pix_data *data, int x, int y, int color);
void			init_func_arr(t_args_func *func_arr);
t_object		*get_object(t_object *obj_ptr, int obj_id);
void			set_pov_plan(double *orient_vec, t_ray *ray_ptr);

//VECTORS

void			vec_scalarprod(double *vector, double scalar, int dimension);
double			dot_prod(double *vec1, double *vec2, int dimension);
void			vec_addition(double *result, double *vec1, double *vec2, int dimension);
void			vec_substract(double *result, double *vec1, double *vec2, int dimension);
double			vec_magnit(double *vec, int dimension);
void			cross_product(double *dst, double *vec1, double *vec2);
void			vec_add_scalar(double *vec, double scalar, int dimension);
void			vec_copy(double *src, double *dst, int dimension);
void			vec_normalize(double *vec, int dimension);

//SHADING

int				convert_rgb_format(double *rgb_arr);
double			max_d(double nb1, double nb2);
int				get_color(t_param *p_ptr, t_ray *ray_ptr, t_object *obj_ptr);

//INTERSECTIONS

double			sphere_intersect(t_ray *ray_ptr, t_object *sphere);
double			get_plane_intersec(t_ray *ray_ptr, double *plane_origin, double *plane_n);
double			plane_intersect(t_ray *ray_ptr, t_object *plane_ptr);
double			square_intersect(t_ray *ray_ptr, t_object *square_ptr);
double			triangle_intersect(t_ray *ray_ptr, t_object *tri_ptr);
double			cylinder_intersect(t_ray *ray_ptr, t_object *cy_ptr);

//HOOKS

int				deal_key(int key, void *param);
int				deal_mouse(int button, int x, int y, void *param);
int				deal_hook(void *params);

//REMOVE
void			print_vec(double *vec);
#endif