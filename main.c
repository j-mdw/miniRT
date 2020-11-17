/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:36:58 by jmaydew           #+#    #+#             */
/*   Updated: 2020/11/17 22:37:04 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void
	set_raytracer(t_param *p_ptr)
{
	t_pix_data	img;

	if (!(p_ptr->mlx_ptr = mlx_init()))
		error_free(p_ptr, "mlx_init failed");
	resize_res(p_ptr);
	p_ptr->mlx_win_ptr = mlx_new_window(p_ptr->mlx_ptr, p_ptr->res_x, \
	p_ptr->res_y, "MiniRT");
	img.img = mlx_new_image(p_ptr->mlx_ptr, p_ptr->res_x, p_ptr->res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	p_ptr->pix_ptr = &img;
	ray_trace(p_ptr);
	mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, img.img, 0, 0);
	mlx_hook(p_ptr->mlx_win_ptr, 17, (1L << 17), deal_hook, p_ptr);
	mlx_key_hook(p_ptr->mlx_win_ptr, deal_key, p_ptr);
	mlx_mouse_hook(p_ptr->mlx_win_ptr, deal_mouse, p_ptr);
	mlx_loop(p_ptr->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_param		params;
	t_args_func func_arr[DIFF_SURFACE];

	if (!(check_open_file(argc, argv, &params)))
		error_free(&params, "");
	init_func_arr(func_arr);
	params.current_camera = get_object(params.object, camera);
	params.func_arr_ptr = func_arr;
	if (params.save)
	{
		save_minirt(&params);
		params.step = 1;
		ray_trace(&params);
		close(params.fd_bmp);
		ft_putstr_fd("Image saved\n", 1);
	}
	else
		set_raytracer(&params);
	free_all(&params);
	return (0);
}
