#ifndef minirt_h
# define minirt_h

#include 	"../libft/libft.h"
#include	"gnl/get_next_line.h"
#include 	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<stddef.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>

typedef enum {
				camera,
				light,
				sphere,
				plane,
				square,
				cylinder,
				triangle,
}	e_elements;

typedef struct s_object {
	int				obj_id;
	float			coord1[3];
	float			coord2[3];
	float			coord3[3];
	float			diameter;
	float			brightness;
	float			height;
	int				rgb;
	int				fov;
	struct s_object	*next_object;
}	t_object;

typedef	struct	s_camera {
	float		coord[3];
	float		orient[3];
	int			fov;
}	t_camera;

typedef struct s_light {
	float		coord[3];
	float		brightness;
	int			rgb;
}	t_light;

typedef	struct s_sphere {
	float		x;
	float		y;
	float		z;
	float		diameter;
	int			rgb;
}	t_sphere;

typedef	struct s_plane {
	float	x;
	float	y;
	float	z;
	float	orient_x;
	float	orient_y;
	float	orient_z;
	int		rgb;
}	t_plane;

typedef	struct s_square {
	float		x;
	float		y;
	float		z;
	float		orient_x;
	float		orient_y;
	float		orient_z;
	float		side_size;
	int			rgb;
}	t_square;

typedef	struct s_cylinder {
	float		x;
	float		y;
	float		z;
	float		orient_x;
	float		orient_y;
	float		orient_z;
	float		diameter;
	float		height;
	int			rgb;
}	t_cylinder;

typedef	struct s_triangle {
	float		x1;
	float		y1;
	float		z1;
	float		x2;
	float		y2;
	float		z2;	
	float		x3;
	float		y3;
	float		z3;
	int			rgb;
}	t_triangle;

typedef	struct	s_elem {
	char			id;
	void			*object;
	struct	s_elem	*next_elem;
}	t_elem;

typedef	struct	s_param {
	int			res_found;
	int			amb_light_found;
	int			res_x;
	int			res_y;
	float		light_ratio;
	int     	light_rgb;
	int			save;
	char		*line;
	char		**line_split;
	char		**extra_split;
/*	t_elem		*elem; */
	e_elements	*elem_index;
	t_object	*object;

}	t_param;

typedef void (*f_parse_funct)(t_param *);


int	ft_strcmp(const char *s1, const char *s2);
int	check_file_extansion(char *filename, char *file_extansion);
int 	ft_isblank(int c);
void    replace_char(char *text, char find, char replace);
int     parse_params(t_param *param_ptr, int fd);
void    error_free(t_param *param, char *error_message);
void    error_free(t_param *param, char *error_message);
void	free_all(t_param *param);
int		ft_isnumber(char *s);
int		array_size(char **arr_ptr);
float   atoitof(t_param *param_ptr, char *s);
int		get_rgb(t_param *param_ptr, char *s);
void	add_new_elem_front(t_param *param_ptr);
void    free_2D_array(char ***ptr);
void	get_coord(char *s, float arr[], t_param *param_ptr, int size);

#endif
