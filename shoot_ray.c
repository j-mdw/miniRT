#include "parsing/minirt.h"

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
    vector_copy(orient_vec, ray_ptr->vec_w, 3);
    ray_ptr->vec_v[0] = 0;
    ray_ptr->vec_v[1] = -1;
    ray_ptr->vec_v[2] = 0;
    if (ray_ptr->vec_w[0] == 0 && (ray_ptr->vec_w[1] == -1 || ray_ptr->vec_w[1] == 1) && ray_ptr->vec_w[2] == 0)
    {
        ray_ptr->vec_v[0] = 0;
        ray_ptr->vec_v[1] = 0;
        ray_ptr->vec_v[2] = -1;
    }
    cross_product(ray_ptr->vec_u, ray_ptr->vec_w, ray_ptr->vec_v);
    cross_product(ray_ptr->vec_v, ray_ptr->vec_w, ray_ptr->vec_u);
    vec_normalize(ray_ptr->vec_u, 3);
    vec_normalize(ray_ptr->vec_v, 3);
    /* printf("POV plan: u:|%f|%f|%f| v:|%f|%f|%f| w:|%f|%f|%f|\n", ray_ptr->vec_u[0], ray_ptr->vec_u[1], ray_ptr->vec_u[2], \
    ray_ptr->vec_v[0], ray_ptr->vec_v[1], ray_ptr->vec_v[2], ray_ptr->vec_w[0], ray_ptr->vec_w[1], ray_ptr->vec_w[2]);
     printf("Dot products: u.v|%f|v.w|%f|u.w|%f|\n", dot_product(ray_ptr->vec_u, ray_ptr->vec_v, 3), dot_product(ray_ptr->vec_v, ray_ptr->vec_w, 3), dot_product(ray_ptr->vec_u, ray_ptr->vec_w, 3));
*/}


void
    init_func_arr(t_args_func *func_arr)
{
    func_arr[sphere] = sphere_intersect;
    func_arr[plane] = plane_intersect;
    func_arr[square] = square_intersect;
    func_arr[triangle] = triangle_intersect;
}

void
    shoot_ray(t_param *p_ptr, t_ray *ray_ptr, int x, int y)
{
    t_object    *surface;
    t_object    *closest_surface;
    double      obj_distance;
    double      store;
    double      tmp_vec1[3];
    double      tmp_vec2[3];

    obj_distance = 0.0;
    surface = p_ptr->object;
    while (surface)
    {
        if (surface->obj_id < DIFF_SURFACE)
        {
            // printf("Light Ray!: %f\n", store);
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
        vec_scalar_product(ray_ptr->direction, obj_distance, 3);
        vector_addition(ray_ptr->vec_intersect, ray_ptr->origin, ray_ptr->direction, 3);
        if (closest_surface->obj_id == sphere)
        {
            vector_substraction(ray_ptr->n_normal, ray_ptr->vec_intersect, closest_surface->coord1, 3);
            vec_scalar_product(ray_ptr->n_normal, 2 / closest_surface->diameter, 3);
        }
        if (closest_surface->obj_id == plane || closest_surface->obj_id == square)
        {
            vector_copy(closest_surface->coord2, ray_ptr->n_normal, 3);
            if (dot_product(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
                vec_scalar_product(ray_ptr->n_normal, -1.0, 3);
        }
        if (closest_surface->obj_id == triangle)
        {
            vector_substraction(tmp_vec1, closest_surface->coord2, closest_surface->coord1, 3);
            vector_substraction(tmp_vec2, closest_surface->coord3, closest_surface->coord2, 3);
            cross_product(ray_ptr->n_normal, tmp_vec1, tmp_vec2);
            vec_normalize(ray_ptr->n_normal, 3);
            if (dot_product(ray_ptr->direction, ray_ptr->n_normal, 3) > 0.0)
                vec_scalar_product(ray_ptr->n_normal, -1.0, 3);
        }
        my_mlx_pixel_put(p_ptr->pix_ptr, x, y, get_color(p_ptr, ray_ptr, closest_surface));
    }
    else
        my_mlx_pixel_put(p_ptr->pix_ptr, x, y, 0);//convert_rgb_format(p_ptr->light_rgb));
}

int
    ray_trace(t_param *p_ptr)
{
    t_ray       ray;
    int         i;
    int         x;
    int         y;

    ray.screen_dist = (((double)p_ptr->res_x) / 2.0) / tan((((double)p_ptr->current_camera->fov) / (2.0 * 180.0)) * M_PI); /* Converting FOV to gradiants as this is what 'tan()' uses */
    i = 0;
    while (i < 3)
    {
        ray.origin[i] = p_ptr->current_camera->coord1[i]; /* Copying camera point of view */
        i++;
    }
    set_pov_plan(p_ptr->current_camera->coord2, &ray);
    vec_scalar_product(ray.vec_w, ray.screen_dist, 3); /* Computing direction vector as origin + (distance * direction(unitary)) */
    vector_copy(ray.vec_u, ray.unit_u, 3);
    vector_copy(ray.vec_v, ray.unit_v, 3);
    x = 0;
    while(x < p_ptr->res_x)
    {
        y = 0;
        ray.vec_u[0] = ray.unit_u[0] * ((((double)p_ptr->res_x) / 2.0) * -1.0 + x);
        ray.vec_u[1] = ray.unit_u[1] * ((((double)p_ptr->res_x) / 2.0) * -1.0 + x);
        ray.vec_u[2] = ray.unit_u[2] * ((((double)p_ptr->res_x) / 2.0) * -1.0 + x);
        while (y < p_ptr->res_y)
        {
            ray.vec_v[0] = ray.unit_v[0] * ((((double)p_ptr->res_y) / 2.0) - y);
            ray.vec_v[1] = ray.unit_v[1] * ((((double)p_ptr->res_y) / 2.0) - y);
            ray.vec_v[2] = ray.unit_v[2] * ((((double)p_ptr->res_y) / 2.0) - y);
            vector_addition(ray.direction, ray.vec_u, ray.vec_v, 3);
            vector_addition(ray.direction, ray.direction, ray.vec_w, 3);
            vec_normalize(ray.direction, 3);
            // printf("ray_y: |%f|%f|%f|\n", ray.direction[0], ray.direction[1], ray.direction[2]);
            shoot_ray(p_ptr, &ray, x, y);
            y++;
        }
        x++;
    }
        printf("Origin: |%f|%f|%f|\n", ray.origin[0], ray.origin[1], ray.origin[2]);
        printf("Direction: |%f|%f|%f|\n", ray.direction[0], ray.direction[1], ray.direction[2]);
        printf("Distance: |%f|%f|%f|\n", ray.screen_dist, (double)p_ptr->current_camera->fov / 2.0, tan(((double)p_ptr->current_camera->fov / 2.0) * M_PI / 180));
    return (x + y);
}