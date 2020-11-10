#include "minirt.h"

int
	deal_key(int key, void *param)
{
	t_object	*tmp_cam;

	if (key == 65307)
	{
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