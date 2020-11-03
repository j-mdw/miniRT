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
#define	SAVE_FLAG "--save"

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
	print_parameters(t_param *param_ptr)
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

int
	deal_key(int key, void *param)
{
	t_object	*tmp_cam;

	if (key == 65307)
	{
		printf("Mais oui!");
		mlx_destroy_window(((t_param *)param)->mlx_ptr, ((t_param *)param)->mlx_win_ptr);
		free_all(param);
		exit(0);
	}
	if (key == 'n')
	{
		if (((t_param *)param)->current_camera->next_object)
			tmp_cam = ((t_param *)param)->current_camera->next_object;
		else
			tmp_cam =  ((t_param *)param)->object;
		while (tmp_cam->obj_id != camera)
		{
			if (!tmp_cam->next_object)
				tmp_cam = ((t_param *)param)->object;
			else
				tmp_cam = tmp_cam->next_object;			
		}
		((t_param *)param)->current_camera = tmp_cam;
		ray_trace(((t_param *)param));
		mlx_put_image_to_window(((t_param *)param)->mlx_ptr, ((t_param *)param)->mlx_win_ptr, ((t_param *)param)->pix_ptr->img, 0, 0);
	}
	if (key == 48)
		printf("saperlipopettes!\n");
	param++;
	printf("Bob %d\n", key);
	return (0);
}

int
	deal_mouse(int button, int x, int y, void *param)
{
	printf("Button: %d, x: %d, y: %d, BS: %d\n", button, x, y, ((t_param *)param)->res_x);
	return (0);
}

int
	deal_hook(void *params)
{
	(void)params;
	exit(0);
	return (0);
}

int
	check_open_file(int argc, char **argv, t_param *p_ptr)
{
	param_struct_init(p_ptr);
	if (argc != 2)
	{
		if (argc == 3 && !(ft_strcmp(argv[2], SAVE_FLAG)))
			p_ptr->save = 1;
		else
		{
			ft_putstr_fd("Incorrect number of arguments or wrong flag", 1);
			return (0);
		}
	}
	if (!check_file_extansion(argv[1], FILE_EXTANSION))
	{
		ft_putstr_fd("Incorrect file extansion", 1);
		return (0);
	}
	if (!(p_ptr->fd = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Failed opening the file, please make sure the file exists\n", 1);
		return (0);
	}
	parse_params(p_ptr);
	print_parameters(p_ptr);
	return (1);
}

int	main(int argc, char **argv)
{
	t_param		params;
	t_pix_data	img;
	t_args_func func_arr[DIFF_SURFACE];

	if (!(check_open_file(argc, argv, &params)))
		error_free(&params, "");
	if(!(params.mlx_ptr = mlx_init()))
		error_free(&params, "mlx_init failed");
	params.mlx_win_ptr = mlx_new_window(params.mlx_ptr, params.res_x, params.res_y, "hello world");
	img.img = mlx_new_image(params.mlx_ptr, params.res_x, params.res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	params.pix_ptr = &img;
	init_func_arr(func_arr);
	params.func_arr_ptr = func_arr;
	params.current_camera = get_object(params.object, camera);
	ray_trace(&params);
	mlx_put_image_to_window(params.mlx_ptr, params.mlx_win_ptr, img.img, 0, 0);
	mlx_hook(params.mlx_win_ptr, 17, (1L << 17), deal_hook, &params);
	mlx_key_hook(params.mlx_win_ptr, deal_key, &params);
	mlx_mouse_hook(params.mlx_win_ptr, deal_mouse, &params);
	mlx_loop(params.mlx_ptr);
	free_all(&params);
	return (0);
}