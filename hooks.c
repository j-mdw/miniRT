#include "minirt.h"

static int
	deal_key_2(t_param *p_ptr, int key)
{
	t_object *tmp_obj;

	if (key == 'l')
	{
		if (!p_ptr->selected_obj)
			p_ptr->selected_obj = p_ptr->object;
		if ((tmp_obj = get_next_object(p_ptr, p_ptr->selected_obj, light)))
		{
			p_ptr->selected_obj = tmp_obj;
			ray_trace(p_ptr);
			mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
			p_ptr->pix_ptr->img, 0, 0);
		}
	}
	if (key == 'r')
	{
		p_ptr->step = 1;
		ray_trace(p_ptr);
		mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
		p_ptr->pix_ptr->img, 0, 0);
		p_ptr->step = STEP;
	}
	return (0);
}

int
	deal_key(int key, void *param)
{
	t_object	*tmp_obj;
	t_param		*p_ptr;

	p_ptr = (t_param *)param;
	if (key == 65307)
	{
		mlx_destroy_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr);
		free_all(param);
		exit(0);
	}
	if (key == 'n' && (tmp_obj = get_next_object(p_ptr, \
	p_ptr->current_camera, camera)))
	{
		p_ptr->current_camera = tmp_obj;
		ray_trace(p_ptr);
		mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
		p_ptr->pix_ptr->img, 0, 0);
	}
	if (key == 'r' || key == 'l')
		deal_key_2(p_ptr, key);
	if ((key >= 65361 && key <= 65364) || ft_strchr("asdwqezx", key))
		make_move(param, key);
	return (0);
}

int
	deal_mouse(int button, int x, int y, void *param)
{
	t_ray	ray;
	t_param	*p_ptr;

	p_ptr = (t_param *)param;
	if (button == 1)
	{
		set_camera_plan(p_ptr, &ray);
		vec_scalarprod(ray.vec_u, (p_ptr->res_x / 2 * -1 + x), 3);
		vec_scalarprod(ray.vec_v, (p_ptr->res_y / 2 - y), 3);
		vec_addition(ray.direction, ray.vec_u, ray.vec_v, 3);
		vec_addition(ray.direction, ray.direction, ray.vec_w, 3);
		vec_normalize(ray.direction, 3);
		if (set_closest(p_ptr, &ray) == 0.0)
			p_ptr->selected_obj = NULL;
		else
			p_ptr->selected_obj = p_ptr->closest_surface;
	}
	if (button == 3)
		p_ptr->selected_obj = NULL;
	printf("Button: %d, x: %d, y: %d\n", button, x, y);
	return (0);
}

int
	deal_hook(void *params)
{
	(void)params;
	exit(0);
	return (0);
}
