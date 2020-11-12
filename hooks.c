#include "minirt.h"

void
	move_camera(t_param *p_ptr, t_ray *ray, int key)
{
	if (key == 65362 )
	{
		vec_scalarprod(ray->vec_v, MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray->vec_v, 3);
	}
	if (key == 65364)
	{
		vec_scalarprod(ray->vec_v, -1 * MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray->vec_v, 3);
	}
	if (key == 65361)
	{
		vec_scalarprod(ray->vec_u, -1 * MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray->vec_u, 3);
	}
	if (key == 65363)
	{
		vec_scalarprod(ray->vec_u, MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray->vec_u, 3);
	}
}

void
	rotate_camera(t_param *p_ptr, t_ray *ray, int key)
{
	vec_normalize(ray->vec_w, 3);
	if (key == 'a' || key == 'd')
	{
		vec_scalarprod(ray->vec_w, cos(RADIAN(ANGLE)), 3);
		vec_scalarprod(ray->vec_u, sin(RADIAN(ANGLE)), 3);
		if (key == 'a')
			vec_scalarprod(ray->vec_u, -1, 3);
		vec_addition(p_ptr->current_camera->coord2, ray->vec_u, ray->vec_w, 3);
	}
	if (key == 'w' || key == 's')
	{
		vec_scalarprod(ray->vec_w, cos(RADIAN(ANGLE)), 3);
		vec_scalarprod(ray->vec_v, sin(RADIAN(ANGLE)), 3);
		if (key == 'w')
			vec_scalarprod(ray->vec_v, -1, 3);
		print_vec(ray->vec_v);
		print_vec(ray->vec_w);
		vec_addition(p_ptr->current_camera->coord2, ray->vec_v, ray->vec_w, 3);
	}
	vec_normalize(p_ptr->current_camera->coord2, 3);
}

void
	make_move(t_param *p_ptr, int key)
{
	t_ray	ray;

	set_pov_plan(p_ptr->current_camera->coord2, &ray);
	if (key >= 65361 && key <= 65364)
		move_camera(p_ptr, &ray, key);
	if (key == 'q')
	{
		vec_scalarprod(ray.vec_w, MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray.vec_w, 3);
	}
	if (key == 'e')
	{
		vec_scalarprod(ray.vec_w, -1 * MOVE_SPEED, 3);
		vec_addition(p_ptr->current_camera->coord1, p_ptr->current_camera->coord1, ray.vec_w, 3);
	}
	if (ft_strchr("adws", key))
		rotate_camera(p_ptr, &ray, key);
	ray_trace(p_ptr);
	mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
	p_ptr->pix_ptr->img, 0, 0);
}

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
	if (key == 'r')
	{
		((t_param *)param)->step = 1;
		ray_trace(((t_param *)param));
		mlx_put_image_to_window(((t_param *)param)->mlx_ptr, ((t_param *)param)->mlx_win_ptr, ((t_param *)param)->pix_ptr->img, 0, 0);
		((t_param *)param)->step = STEP;
	}
	if ((key >= 65361 && key <= 65364) || ft_strchr("asdwqe", key))
		make_move(param, key);
	printf("Key: %d\n", key);
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