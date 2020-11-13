#include "minirt.h"

void
	move_object(double *position, t_ray *ray, int key)
{
	double	tmp_vec[3];

	if (key >= 65361 && key <= 65364)
	{
		vec_copy(ray->vec_u, tmp_vec, 3);
		if (key == 65362 || key == 65364)
			vec_copy(ray->vec_v, tmp_vec, 3);
		vec_scalarprod(tmp_vec, MOVE_SPEED, 3);
		if (key == 65364 || key == 65361)
				vec_scalarprod(tmp_vec, -1, 3);
		vec_addition(position, position, tmp_vec, 3);
	}
	if (key == 'q' || key == 'e')
	{
		vec_copy(ray->vec_w, tmp_vec, 3);
		vec_scalarprod(tmp_vec, MOVE_SPEED, 3);
		if (key == 'e')
			vec_scalarprod(tmp_vec, -1, 3);
		vec_addition(position, position, tmp_vec, 3);
	}
}

void
	rotate_object(t_param *p_ptr, t_ray *ray, int key)
{
	printf("_Initial direction_\n");
	print_vec(p_ptr->current_camera->coord2);
	printf("** POV befor modif **\n");
	print_vec(ray->vec_u);
	print_vec(ray->vec_v);
	print_vec(ray->vec_w);
	printf("**\n");

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
			print_vec(p_ptr->current_camera->coord2);
}

void
	make_move(t_param *p_ptr, int key)
{
	t_ray		ray;
	t_object	*object;

	if (p_ptr->selected_obj)
		object = p_ptr->selected_obj;
	else
		object = p_ptr->current_camera;
	set_pov_plan(p_ptr->current_camera->coord2, &ray);
	if ((key >= 65361 && key <= 65364) || key == 'q' || key == 'e')
	{
		move_object(object->coord1, &ray, key);
		if (object->obj_id == triangle)
		{
			move_object(object->coord2, &ray, key);
			move_object(object->coord3, &ray, key);
		}
	}
	if (ft_strchr("adws", key))
		rotate_object(p_ptr, &ray, key);
	ray_trace(p_ptr);
	mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
	p_ptr->pix_ptr->img, 0, 0);
}

t_object
	*get_next_object(t_param *p_ptr, t_object *current_obj, int obj_id)
{
	t_object *tmp_obj;
	t_object *store;

	store = current_obj;
	if (current_obj->next_object)
			tmp_obj = current_obj->next_object;
	else
		tmp_obj =  p_ptr->object;
	while (tmp_obj->obj_id != obj_id)
	{
		if (!tmp_obj->next_object)
			tmp_obj = p_ptr->object;
		else if (tmp_obj == store)
			return (NULL);
		else
			tmp_obj = tmp_obj->next_object;
	}
	if (tmp_obj != store)
		return (tmp_obj);
	return (NULL);
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
	if (key == 'n' && (tmp_obj = get_next_object(p_ptr, p_ptr->current_camera, camera)))
	{
		p_ptr->current_camera = tmp_obj;
		ray_trace(p_ptr);
		mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, p_ptr->pix_ptr->img, 0, 0);
	}
	if (key == 'r')
	{
		p_ptr->step = 1;
		ray_trace(p_ptr);
		mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, p_ptr->pix_ptr->img, 0, 0);
		p_ptr->step = STEP;
	}
	if ((key >= 65361 && key <= 65364) || ft_strchr("asdwqe", key))
		make_move(param, key);
	if (key == 'l')
	{
		if (!p_ptr->selected_obj)
			p_ptr->selected_obj = p_ptr->object;
		if ((tmp_obj = get_next_object(p_ptr, p_ptr->selected_obj, light)))
		{
			p_ptr->selected_obj = tmp_obj;
			ray_trace(p_ptr);
			mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, p_ptr->pix_ptr->img, 0, 0);
		}
	}
	printf("Key: %d\n", key);
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