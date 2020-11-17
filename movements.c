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
	rotate_object(t_object *obj_ptr, t_ray *ray, int key)
{
	vec_normalize(ray->vec_w, 3);
	if (key == 'a' || key == 'd')
	{
		vec_scalarprod(ray->vec_w, cos(RADIAN(ANGLE)), 3);
		vec_scalarprod(ray->vec_u, sin(RADIAN(ANGLE)), 3);
		if (key == 'a')
			vec_scalarprod(ray->vec_u, -1, 3);
		vec_addition(obj_ptr->coord2, ray->vec_u, ray->vec_w, 3);
		vec_copy(ray->vec_v, obj_ptr->coord3, 3);
	}
	if (key == 'w' || key == 's')
	{
		vec_scalarprod(ray->vec_w, cos(RADIAN(ANGLE)), 3);
		vec_scalarprod(ray->vec_v, sin(RADIAN(ANGLE)), 3);
		if (key == 'w')
		{
			vec_scalarprod(ray->vec_v, -1, 3);
			vec_addition(obj_ptr->coord2, ray->vec_v, ray->vec_w, 3);
			vec_scalarprod(ray->vec_v, -1, 3);
		}
		else
			vec_addition(obj_ptr->coord2, ray->vec_v, ray->vec_w, 3);
		vec_copy(ray->vec_v, obj_ptr->coord3, 3);
	}
	vec_normalize(obj_ptr->coord2, 3);
}

void
	resize_object(t_object *obj_ptr, int key)
{
	int	delta;
	int	new_size;

	if (key == 'z')
		delta = S_DELTA;
	else if (key == 'x')
		delta = S_DELTA * -1;
	if (obj_ptr->obj_id == square || obj_ptr->obj_id == cylinder)
	{
		if ((new_size = obj_ptr->height + delta) < INT_MAX && new_size > 0)
			obj_ptr->height += delta;
	}
	if (obj_ptr->obj_id == sphere || obj_ptr->obj_id == cylinder)
	{
		if ((new_size = obj_ptr->diameter + delta) < INT_MAX && new_size > 0)
			obj_ptr->diameter += delta;
	}
}

static void
	make_move_2(t_param	*p_ptr, t_ray *ray_ptr, t_object *object, int key)
{
	if (ft_strchr("adws", key))
	{
		if (object->obj_id == sphere || \
		object->obj_id == light || object->obj_id == triangle)
			object = p_ptr->current_camera;
		set_pov_plan(object->coord2, object->coord3, ray_ptr);
		rotate_object(object, ray_ptr, key);
	}
	if ((key == 'z' || key == 'x') && (object->obj_id == sphere || \
	object->obj_id == square || object->obj_id == cylinder))
		resize_object(object, key);
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
	if ((key >= 65361 && key <= 65364) || key == 'q' || key == 'e')
	{
		set_pov_plan(p_ptr->current_camera->coord2, \
		p_ptr->current_camera->coord3, &ray);
		move_object(object->coord1, &ray, key);
		if (object->obj_id == triangle)
		{
			move_object(object->coord2, &ray, key);
			move_object(object->coord3, &ray, key);
		}
	}
	make_move_2(p_ptr, &ray, object, key);
	ray_trace(p_ptr);
	mlx_put_image_to_window(p_ptr->mlx_ptr, p_ptr->mlx_win_ptr, \
	p_ptr->pix_ptr->img, 0, 0);
}
