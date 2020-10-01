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
	param_ptr->object = NULL;
	param_ptr->extra_split = NULL;
}

void
	display_parameters(t_param *param_ptr)
{
	t_object	*object_ptr; /* for iteration the linked list for testing */
	
	printf("Resoultion parameters: |x: %d|y: %d|\n", param_ptr->res_x, param_ptr->res_y);
	printf("Light ratio: %f\n", param_ptr->light_ratio);
	printf("Light RGB is: %#x\n", param_ptr->light_rgb);
	object_ptr = param_ptr->object;
	while (object_ptr)
	{
		if (object_ptr->obj_id == camera)
			printf("Camera inputs:\ncoordinates |%f|%f|%f|\norient_vector |%f|%f|%f|\nFOV: %d\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->fov);
		else if (object_ptr->obj_id == light)
			printf("Light inputs:\ncoordinates |%f|%f|%f|\nRatio |%f|\nRgb |%#x|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->brightness, object_ptr->rgb);
		else if (object_ptr->obj_id == sphere)
			printf("Sphere inputs:\ncoordinates |%f|%f|%f|\nDiameter |%f|\nRgb |%#x|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->diameter, object_ptr->rgb);
		else if (object_ptr->obj_id == plane)
			printf("Plane inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nRgb |%#x|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->rgb);
		else if (object_ptr->obj_id == square)
			printf("Square inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nHeight |%f|\nRgb |%#x|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->height, object_ptr->rgb);
		else if (object_ptr->obj_id == cylinder)
			printf("Cylinder inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nRgb |%#x|\nDiameter |%f|\nHeight |%f|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->rgb, object_ptr->diameter, object_ptr->height);
		else if (object_ptr->obj_id == triangle)
			printf("Triangle inputs:\ncoordinates1 |%f|%f|%f|\nCoordinates2 |%f|%f|%f|\nCoordinates3 |%f|%f|%f|\nRgb |%#x|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->coord3[0], object_ptr->coord3[1], object_ptr->coord3[2], object_ptr->rgb);
		object_ptr = object_ptr->next_object;
	}
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
	display_parameters(&params);
	free_all(&params);
	return (0);
}