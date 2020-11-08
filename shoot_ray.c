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
    /* printf("POV plan: u:|%f|%f|%f| v:|%f|%f|%f| w:|%f|%f|%f|\n", ray_ptr->vec_u[0], ray_ptr->vec_u[1], ray_ptr->vec_u[2], \
    ray_ptr->vec_v[0], ray_ptr->vec_v[1], ray_ptr->vec_v[2], ray_ptr->vec_w[0], ray_ptr->vec_w[1], ray_ptr->vec_w[2]);
     printf("Dot products: u.v|%f|v.w|%f|u.w|%f|\n", dot_product(ray_ptr->vec_u, ray_ptr->vec_v, 3), dot_product(ray_ptr->vec_v, ray_ptr->vec_w, 3), dot_product(ray_ptr->vec_u, ray_ptr->vec_w, 3));
*/}

double
    sphere_intersect(t_ray *ray_ptr, t_object *sphere)
{
    t_quadratic quad_params;
    double      temp_vec[3];

    quad_params.a = dot_product(ray_ptr->direction, ray_ptr->direction, 3);
    vector_substraction(temp_vec, ray_ptr->origin, sphere->coord1, 3); /* (e - c) */
//    printf("(e - c): |%f|%f|%f|\n", temp_vec[0], temp_vec[1], temp_vec[2]);
    quad_params.b = 2.0 * dot_product(ray_ptr->direction, temp_vec, 3); /* 2d.(e-c) */
    quad_params.c = dot_product(temp_vec, temp_vec, 3) - pow((sphere->diameter / 2.0), 2);
    quad_params.discrim = pow(quad_params.b, 2) - 4 * quad_params.a * quad_params.c;
    if (quad_params.discrim < 0.0)
    {
//        printf("No HIT\n");
        return (-1.0);
    }
    else if (quad_params.discrim == 0)
        return (-quad_params.b / (2 * quad_params.a));
    else
    {
        quad_params.solut_1 = (-quad_params.b - sqrt(quad_params.discrim)) / (2 * quad_params.a);
        quad_params.solut_2 = (-quad_params.b + sqrt(quad_params.discrim)) / (2 * quad_params.a);
//        printf("Direction: |%f|%f|%f|\n", ray_ptr->direction[0], ray_ptr->direction[1], ray_ptr->direction[2]);
//        printf("solution 1: %f, solution 2: %f\n", solut_1, solut_2);
//        printf("a: %f, b: %f, c: %f, discrim: %f\n", a, b, c, discrim);
        if (pow(quad_params.solut_1, 2) < pow(quad_params.solut_2, 2)) //Not sure this is fine, negative would be behind the camera I think (but then could I get negative values?? considering the vector direction that woud probably not happen?)
            return (quad_params.solut_1);
        return (quad_params.solut_2);
    }
}

// (p0 - l0) . n / l . n

double
    get_plane_intersect(t_ray *ray_ptr, double *plane_origin, double *plane_n)
{
    double  intersect;
    double  tmp_val;
    double  tmp_vec[3];

    if ((tmp_val = dot_product(ray_ptr->direction, plane_n, 3)) == 0.0)
        return(0.0);
    vector_substraction(tmp_vec, plane_origin, ray_ptr->origin, 3);
    intersect = dot_product(tmp_vec, plane_n, 3) / tmp_val;
    // printf("Plane intersect: %f\n", intersect);
    return (intersect);
}

double
    plane_intersect(t_ray *ray_ptr, t_object *plane_ptr)
{
    return (get_plane_intersect(ray_ptr, plane_ptr->coord1, plane_ptr->coord2));
    // double  intersect;
    // double  tmp_val;
    // double  tmp_vec[3];

    // // printf("Ray dir: %f|%f|%f\n", ray_ptr->direction[0], ray_ptr->direction[1], ray_ptr->direction[2]);
    // if ((tmp_val = dot_product(ray_ptr->direction, plane_ptr->coord2, 3)) == 0.0)
    //     return(0.0);
    // // printf("Dir . n: %.4f\t", tmp_val);
    // vector_substraction(tmp_vec, plane_ptr->coord1, ray_ptr->origin, 3);
    // // printf("Center - ray o: %.4f|%.4f|%.4f\t", tmp_vec[0], tmp_vec[1], tmp_vec[2]);
    // intersect = dot_product(tmp_vec, plane_ptr->coord2, 3) / tmp_val;
    // // printf("Previous . n: %.4f, Intersect %.4f\n", tmp_val, intersect);
    // return (intersect);
}

// double
//     disc_intersect(t_ray *ray_ptr, t_object *square_ptr)
// {
//     double  ray_plane[3];
//     double  sq_to_inter[3];
//     double  tmp_val;
//     // double  length;
//     // t_ray   tmp_pov;

//     if ((tmp_val = plane_intersect(ray_ptr, square_ptr)) > 0.0)
//     {
//         // printf("Were here\n");
//         vector_copy(ray_ptr->direction, ray_plane, 3);
//         vec_scalar_product(ray_plane, tmp_val, 3);
//         vector_addition(ray_plane, ray_plane, ray_ptr->origin, 3);
//         vector_substraction(sq_to_inter, ray_plane, square_ptr->coord1, 3);
//         // printf("Length: %f, Height: %f, max length: %f\n", vector_magnitude(sq_to_inter, 3), square_ptr->height, sqrt(pow(square_ptr->height / 2, 2) * 2));
//         if (vector_magnitude(sq_to_inter, 3) <= sqrt(pow(square_ptr->height / 2, 2) * 2))
//         {
//             // printf("Center to intersection distance: %f\n", vector_magnitude(sq_to_inter, 3));
//             return (tmp_val);
//         }
//     }
//     return (0.0);
// }

double
    square_intersect(t_ray *ray_ptr, t_object *square_ptr)
{
    double  ray_plane[3];
    double  sq_to_inter[3];
    double  tmp_val;
    // double  length;
    // t_ray   tmp_pov;

    if ((tmp_val = plane_intersect(ray_ptr, square_ptr)) > 0.0)
    {
        // printf("Were here\n");
        vector_copy(ray_ptr->direction, ray_plane, 3);
        vec_scalar_product(ray_plane, tmp_val, 3);
        vector_addition(ray_plane, ray_plane, ray_ptr->origin, 3);
        vector_substraction(sq_to_inter, ray_plane, square_ptr->coord1, 3);
        // printf("Length: %f, Height: %f, max length: %f\n", vector_magnitude(sq_to_inter, 3), square_ptr->height, sqrt(pow(square_ptr->height / 2, 2) * 2));
        if (vector_magnitude(sq_to_inter, 3) <= sqrt(pow(square_ptr->height / 2, 2) * 2))
        {
            // printf("Center to intersection distance: %f\n", vector_magnitude(sq_to_inter, 3));
            return (tmp_val);
        }
        // length = vector_magnitude(sq_to_inter, 3);
        // vec_normalize(sq_to_inter, 3);
        // set_pov_plan(square_ptr->coord2, &tmp_pov);
        // tmp_pov.screen_dist = dot_product(tmp_pov.vec_u, sq_to_inter, 3);
        // tmp_val = tmp_pov.screen_dist / ((square_ptr->height / 2));
        // // printf("Cosine: %f\n", tmp_val);
        // tmp_val = (square_ptr->height / 2) / tmp_val;
        // // printf("Lenght from center: |%f|%f|\n", tmp_val, length);
        // if (pow(tmp_val, 2) >= pow(length, 2))
        //     return (length);
    }
    return (0.0);
}

double
    triangle_intersect(t_ray *ray_ptr, t_object *tri_ptr)
{
    double  tri_n[3];
    double  plane_dist;
    double  tmp_vec1[3];
    double  tmp_vec2[3];
    double  tmp_vec3[3];
    double  point_inter[3];
    int     sum_check;

    vector_substraction(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
    vector_substraction(tmp_vec2, tri_ptr->coord3, tri_ptr->coord2, 3);
    cross_product(tri_n, tmp_vec1, tmp_vec2);
    vec_normalize(tri_n, 3);
    if (dot_product(tri_n, ray_ptr->direction, 3) > 0.0)
        vec_scalar_product(tri_n, -1.0, 3);
    // printf("Normal: |%.4f|%.4f|%.4f\n", tri_n[0], tri_n[1], tri_n[2]);
    if ((plane_dist = get_plane_intersect(ray_ptr, tri_ptr->coord1, tri_n)) < 0.0)
    {  
        // printf("Not in plane: %.2f\n", plane_dist);
        return (0.0);
    }
    // printf("Plane dist: %f\n", plane_dist);
    vector_copy(ray_ptr->direction, point_inter, 3);
    vec_scalar_product(point_inter, plane_dist, 3);
    vector_addition(point_inter, point_inter, ray_ptr->origin, 3);

    vector_substraction(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
    vector_substraction(tmp_vec2, point_inter, tri_ptr->coord1, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 1: %f\n", dot_product(tri_n, tmp_vec3, 3));
    sum_check = 0;
    if (dot_product(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;

    vector_substraction(tmp_vec1, tri_ptr->coord3, tri_ptr->coord2, 3);
    vector_substraction(tmp_vec2, point_inter, tri_ptr->coord2, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 2: %f\n", dot_product(tri_n, tmp_vec3, 3));
    if (dot_product(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;
    
    vector_substraction(tmp_vec1, tri_ptr->coord1, tri_ptr->coord3, 3);
    vector_substraction(tmp_vec2, point_inter, tri_ptr->coord3, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 3: %f\n", dot_product(tri_n, tmp_vec3, 3));
    if (dot_product(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;
    if (sum_check == 3 || sum_check == 0)
    {
        // printf("### WINWINWINWIN ###\n");
        return (plane_dist);
    }
    return (0.0);
}

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
        my_mlx_pixel_put(p_ptr->pix_ptr, x, y, convert_rgb_format(p_ptr->light_rgb));
}

int
    ray_trace(t_param *p_ptr)
{
    t_ray       ray;
    int         i;
    int         x;
    int         y;

    ray.screen_dist = (((double)p_ptr->res_x) / 2.0) / tan((((double)p_ptr->current_camera->fov) / 2.0) * M_PI / 180); /* Converting FOV to gradiants as this is what 'tan()' uses */
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