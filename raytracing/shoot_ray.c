#include "../minirt.h"

t_object
    *get_object(t_object *obj_ptr, int obj_id)
{
    while (obj_ptr->obj_id != obj_id && obj_ptr->next_object != NULL)
        obj_ptr = obj_ptr->next_object;
    if (obj_ptr->obj_id == obj_id)
        return(obj_ptr);
    return (NULL);
}

void
    set_pov_plan(double *orient_vec, t_ray *ray_ptr)
{
    vec_copy(orient_vec, ray_ptr->vec_w, 3);
    ray_ptr->vec_v[0] = 0;
    ray_ptr->vec_v[1] = -1;
    ray_ptr->vec_v[2] = 0;
    if (ray_ptr->vec_w[0] == 0 && (ray_ptr->vec_w[1] == -1 || \
    ray_ptr->vec_w[1] == 1) && ray_ptr->vec_w[2] == 0)
    {
        ray_ptr->vec_v[0] = 0;
        ray_ptr->vec_v[1] = 0;
        ray_ptr->vec_v[2] = -1;
    }
    cross_product(ray_ptr->vec_u, ray_ptr->vec_w, ray_ptr->vec_v);
    cross_product(ray_ptr->vec_v, ray_ptr->vec_w, ray_ptr->vec_u);
    vec_normalize(ray_ptr->vec_u, 3);
    vec_normalize(ray_ptr->vec_v, 3);
}

void
    init_func_arr(t_args_func *func_arr)
{
    func_arr[sphere] = sphere_intersect;
    func_arr[plane] = plane_intersect;
    func_arr[square] = square_intersect;
    func_arr[triangle] = triangle_intersect;
    func_arr[cylinder] = cylinder_intersect;
}

void
    set_normal(t_object *surface, t_ray *ray_ptr)
{
    double  tmp_vec1[3];
    double  tmp_vec2[3];

    if (surface->obj_id == sphere)
    {
        vec_substract(ray_ptr->n_normal, ray_ptr->vec_intersect, surface->coord1, 3);
        vec_scalarprod(ray_ptr->n_normal, 2 / surface->diameter, 3);
    }
    if (surface->obj_id == plane || surface->obj_id == square)
    {
        vec_copy(surface->coord2, ray_ptr->n_normal, 3);
        if (dot_prod(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
            vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
    }
    if (surface->obj_id == triangle)
    {
        vec_substract(tmp_vec1, surface->coord2, surface->coord1, 3);
        vec_substract(tmp_vec2, surface->coord3, surface->coord2, 3);
        cross_product(ray_ptr->n_normal, tmp_vec1, tmp_vec2);
        vec_normalize(ray_ptr->n_normal, 3);
        if (dot_prod(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
            vec_scalarprod(ray_ptr->n_normal, -1.0, 3);
    }
    if (surface->obj_id == cylinder)
    {
        vec_substract(tmp_vec1, ray_ptr->vec_intersect, surface->coord1, 3);
        vec_copy(surface->coord2, tmp_vec2, 3);
        vec_scalarprod(tmp_vec2, dot_prod(tmp_vec1, tmp_vec2, 3), 3);
        vec_substract(ray_ptr->n_normal, tmp_vec1, tmp_vec2, 3);
        vec_normalize(ray_ptr->n_normal, 3);
    }
}

void
    fill_window(t_param *p_ptr, int color, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i < p_ptr->step && x < p_ptr->res_x)
    {
        j = 0;
        while(j < p_ptr->step && y < p_ptr->res_y)
        {
            my_mlx_pixel_put(p_ptr->pix_ptr, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void
    shoot_ray(t_param *p_ptr, t_ray *ray_ptr, int x, int y)
{
    t_object    *surface;
    t_object    *closest_surface;
    double      obj_distance;
    double      store;
    int         color;

    obj_distance = 0.0;
    surface = p_ptr->object;
    while (surface)
    {
        if (surface->obj_id < DIFF_SURFACE)
        {
            store = p_ptr->func_arr_ptr[surface->obj_id](ray_ptr, surface);
            if (store > 0.0 && (store < obj_distance || obj_distance == 0.0))
            {
                obj_distance = store;
                closest_surface = surface;
            }
        }
        surface = surface->next_object;
    }
    if (obj_distance > 0.0)
    {
        vec_copy(ray_ptr->direction, ray_ptr->vec_intersect, 3);
        vec_scalarprod(ray_ptr->vec_intersect, obj_distance, 3);
        vec_addition(ray_ptr->vec_intersect, ray_ptr->origin, ray_ptr->vec_intersect, 3);
        set_normal(closest_surface, ray_ptr);
        color =  get_color(p_ptr, ray_ptr, closest_surface);
    }
    else
        color = 0;
    fill_window(p_ptr, color, x, y);
}

void
    set_camera_plan(t_param *p_ptr, t_ray *ray_ptr)
{
    ray_ptr->screen_dist = (((double)p_ptr->res_x) / 2.0) / \
    tan((((double)p_ptr->current_camera->fov) / (2.0 * 180.0)) * M_PI);
    ray_ptr->origin[0] = p_ptr->current_camera->coord1[0];
    ray_ptr->origin[1] = p_ptr->current_camera->coord1[1];
    ray_ptr->origin[2] = p_ptr->current_camera->coord1[2];
    set_pov_plan(p_ptr->current_camera->coord2, ray_ptr);
    vec_scalarprod(ray_ptr->vec_w, ray_ptr->screen_dist, 3);
    vec_copy(ray_ptr->vec_u, ray_ptr->unit_u, 3);
    vec_copy(ray_ptr->vec_v, ray_ptr->unit_v, 3);
}

int
    ray_trace(t_param *p_ptr)
{
    t_ray       ray;
    int         x;
    int         y;

    set_camera_plan(p_ptr, &ray);
    x = 0;
    while(x < p_ptr->res_x && !(y = 0))
    {
        ray.vec_u[0] = ray.unit_u[0] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
        ray.vec_u[1] = ray.unit_u[1] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
        ray.vec_u[2] = ray.unit_u[2] * ((double)p_ptr->res_x / 2.0 * -1.0 + x);
        while (y < p_ptr->res_y)
        {
            ray.vec_v[0] = ray.unit_v[0] * ((double)p_ptr->res_y / 2.0 - y);
            ray.vec_v[1] = ray.unit_v[1] * ((double)p_ptr->res_y / 2.0 - y);
            ray.vec_v[2] = ray.unit_v[2] * ((double)p_ptr->res_y / 2.0 - y);
            vec_addition(ray.direction, ray.vec_u, ray.vec_v, 3);
            vec_addition(ray.direction, ray.direction, ray.vec_w, 3);
            vec_normalize(ray.direction, 3);
            shoot_ray(p_ptr, &ray, x, y);
            y += p_ptr->step;
        }
        x += p_ptr->step;
    }
    return (x + y);
}