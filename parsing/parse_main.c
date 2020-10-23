/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_main.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: jmaydew <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2020/10/01 18:12:39 by jmaydew		   #+#	  #+#			  */
/*	 Updated: 2020/10/01 18:12:44 by jmaydew		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minirt.h"
#define	FILE_EXTANSION ".rt"
#define	FLAG "--save"

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
}

void
	display_parameters(t_param *param_ptr)
{
	t_object	*object_ptr;

	printf("Resoultion parameters: |x: %d|y: %d|\n", param_ptr->res_x, param_ptr->res_y);
	printf("Light ratio: %f\n", param_ptr->light_ratio);
	printf("Light RGB is: %.4f|%.4f|%.4f|\n", param_ptr->light_rgb[0], param_ptr->light_rgb[1], param_ptr->light_rgb[2]);
	object_ptr = param_ptr->object;
	while (object_ptr)
	{
		if (object_ptr->obj_id == camera)
			printf("Camera inputs:\ncoordinates |%f|%f|%f|\norient_vector |%f|%f|%f|\nFOV: %d\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->fov);
		else if (object_ptr->obj_id == light)
			printf("Light inputs:\ncoordinates |%f|%f|%f|\nRatio |%f|\nRgb |%.4f|%.4f|%.4f||\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->brightness, object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2]);
		else if (object_ptr->obj_id == sphere)
			printf("Sphere inputs:\ncoordinates |%f|%f|%f|\nDiameter |%f|\nRgb |%.4f|%.4f|%.4f||\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->diameter, object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2]);
		else if (object_ptr->obj_id == plane)
			printf("Plane inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nRgb |%.4f|%.4f|%.4f||\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2]);
		else if (object_ptr->obj_id == square)
			printf("Square inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nHeight |%f|\nRgb |%.4f|%.4f|%.4f||\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->height, object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2]);
		else if (object_ptr->obj_id == cylinder)
			printf("Cylinder inputs:\ncoordinates |%f|%f|%f|\nOrientation vector |%f|%f|%f|\nRgb |%.4f|%.4f|%.4f||\nDiameter |%f|\nHeight |%f|\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2], object_ptr->diameter, object_ptr->height);
		else if (object_ptr->obj_id == triangle)
			printf("Triangle inputs:\ncoordinates1 |%f|%f|%f|\nCoordinates2 |%f|%f|%f|\nCoordinates3 |%f|%f|%f|\nRgb |%.4f|%.4f|%.4f||\n", object_ptr->coord1[0], object_ptr->coord1[1], object_ptr->coord1[2], object_ptr->coord2[0], object_ptr->coord2[1], object_ptr->coord2[2], object_ptr->coord3[0], object_ptr->coord3[1], object_ptr->coord3[2], object_ptr->rgb[0], object_ptr->rgb[1],object_ptr->rgb[2]);
		object_ptr = object_ptr->next_object;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_param		params;
	void		*mlx;
	void		*mlx_win;
	t_pix_data	img;
	t_args_func func_arr[DIFF_SURFACE];

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
/*	params.light_ratio = 1.0;  Useless, just to avoid errors at compile for now 
	params.light_ratio += 1.0;  Same */
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
	parse_params(&params, fd);
	display_parameters(&params);
	if(!(mlx = mlx_init()))
		error_free(&params, "mlx_init failed");
	mlx_win = mlx_new_window(mlx, params.res_x, params.res_y, "hello world");
	img.img = mlx_new_image(mlx, params.res_x, params.res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	params.pix_ptr = &img;
	printf("KSGSDF\n");
	init_func_arr(func_arr);
	params.func_arr_ptr = func_arr;
	ray_trace(&params);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_all(&params);
	return (0);
}
