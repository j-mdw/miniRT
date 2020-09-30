#include "minirt.h"

#define	FILE_EXTANSION	".rt"
#define	FLAG "--save"


void	param_struct_init(t_param *param_ptr)
{
	param_ptr->save = 0;
	param_ptr->res_found = 0;
	param_ptr->amb_light_found = 0;
	param_ptr->line = NULL;
	param_ptr->line_split = NULL;
	param_ptr->elem = NULL;
	param_ptr->extra_split = NULL;
}

int	main(int argc, char **argv)
{
	int			fd;
	t_param		params;

	param_struct_init(&params);
	if (argc != 2)
	{
		if (argc == 3 && !(ft_strcmp(argv[2], FLAG)))
			params.save = 1;
		else
		{
			ft_putstr_fd("Incorrect number of arguments", 1);
			return (-1);
		}
	}
	params.light_ratio = 1.0; /* Useless, just to avoid errors at compile for now */
	params.light_ratio += 1.0; /* Same */
	if (!check_file_extansion(argv[1], FILE_EXTANSION))
	{
		ft_putstr_fd("Incorrect file extansion", 1);
		return (-1);
	}
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Failed opening the file, please make sure the file exists\n", 1);
		return (-1);
	}
	ft_putstr_fd("File Open\n", 1);
	parse_params(&params, fd);
	printf("Resoultion parameters: |x: %d|y: %d|\n", params.res_x, params.res_y);
	printf("Light ratio: %f\n", params.light_ratio);
	printf("Light RGB is: %#x\n", params.light_rgb);
/*	t_camera *cam_ptr;*/
	t_param *param_ptr;
	param_ptr = &params;
	while (param_ptr->elem)
	{
		if (param_ptr->elem->id == camera)
			printf("Camera inputs:\ncoordinates |%f|%f|%f|\norient_vector |%f|%f|%f|\nFOV: %d\n", ((t_camera *)param_ptr->elem->object)->coord[0], ((t_camera *)param_ptr->elem->object)->coord[1], ((t_camera *)param_ptr->elem->object)->coord[2], ((t_camera *)param_ptr->elem->object)->orient[0], ((t_camera *)param_ptr->elem->object)->orient[1], ((t_camera *)param_ptr->elem->object)->orient[2], ((t_camera *)param_ptr->elem->object)->fov);
		param_ptr->elem = param_ptr->elem->next_elem;
	}
	free_all(&params);
	return (0);
}
