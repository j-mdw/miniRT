#include "parsing/minirt.h"
#ifndef M_PI
# define M_PI acos(-1.0)
#endif

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
    vec_scalar_product(double *vector, double scalar, int dimension)
{
    int i;

    i = 0;
    while (i < dimension)
    {
        vector[i] *= scalar;
        i++;
    }
}

double
    dot_product(double *vec1, double *vec2, int dimension)
{
    int     i;
    double  result;

    i = 0;
    result = 0.0;
    while (i < dimension)
    {
        result += (vec1[i] * vec2[i]);
        i++;
    }
    return (result);
}

void
    vector_addition(double *result, double *vec1, double *vec2, int dimension)
{
    int     i;

    i = 0;
    while (i < dimension)
    {
        result[i] = vec1[i] + vec2[i];
        i++;
    }
}

void
    vector_substraction(double *result, double *vec1, double *vec2, int dimension)
{
    int     i;

    i = 0;
    while (i < dimension)
    {
        result[i] = vec1[i] - vec2[i];
        i++;
    }
}

double
    shoot_ray(t_param *p_ptr, t_ray *ray_ptr)
{
    double      discrim;
    double      a;
    double      b;
    double      c;
    double      temp_vec[3];
    double      solut_1;
    double      solut_2;
    t_object    *sphere1;

/*    
    At^2 + Bt + C:
        (d.d)*t^2 + 2d.(e-c)t +(e-c).(e-c) - R^2
    B^2 - 4AC:
        B^2: (2d.(e-c))^2
        4AC: 4 * (d.d) * ((e-c).(e-c) - R^2)
*/
    sphere1 = p_ptr->object;
    while (sphere1->obj_id != sphere)
    {
    //    printf("Obj ID: %d\n", sphere1->obj_id);
        sphere1 = sphere1->next_object;
    }
    a = dot_product(ray_ptr->direction, ray_ptr->direction, 3);
    vector_substraction(temp_vec, ray_ptr->origin, sphere1->coord1, 3); /* (e - c) */
//    printf("(e - c): |%f|%f|%f|\n", temp_vec[0], temp_vec[1], temp_vec[2]);
    b = 2.0 * dot_product(ray_ptr->direction, temp_vec, 3); /* 2d.(e-c) */
    c = dot_product(temp_vec, temp_vec, 3) - pow((sphere1->diameter / 2.0), 2);
    discrim = pow(b, 2) - 4 * a * c;
//    printf("a: %f, b: %f, c: %f, discrim: %f\n", a, b, c, discrim);
    if (discrim < 0.0)
    {
//        printf("No HIT\n");
        return (-1.0);
    }
    else if (discrim == 0)
        return (-b / (2 * a));
    else
    {
        solut_1 = (-b - sqrt(discrim)) / (2 * a);
        solut_2 = (-b + sqrt(discrim)) / (2 * a);
  //      printf("solution 1: %f, solution 2: %f\n", solut_1, solut_2);
        if (pow(solut_1, 2) < pow(solut_2, 2))
            return (solut_1);
        return (solut_2);
    }
//    printf("a: %f, b: %f, c: %f, discrim: %f\n", a, b, c, discrim);
    return (discrim);
}

double
    vector_magnitude(double *vec, int dimension)
{
    int     i;
    double  result;

    i = 0;
    result = 0;
    while (i < dimension)
    {
        result += pow(vec[i], 2);
        i++;
    }
    return (sqrt(result));
}

void
    cross_product(double *dst, double *vec1, double *vec2)
{
    dst[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
    dst[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
    dst[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
}

void
    set_pov_plan(t_object *cam_ptr, t_ray *ray_ptr)
{
    int     i;
    double  magnitude;

    i = 0;
    magnitude = vector_magnitude(cam_ptr->coord2, 3);
    while (i < 3)
    {
        ray_ptr->vec_w[i] = cam_ptr->coord2[i] / magnitude; /*Copying camera view point in vec w and converting to a unit vector */
        i++;
    }
    ray_ptr->vec_v[0] = ray_ptr->vec_w[0];
    ray_ptr->vec_v[1] = ray_ptr->vec_w[2];
    ray_ptr->vec_v[2] = ray_ptr->vec_w[1] * -1;
    cross_product(ray_ptr->vec_u, ray_ptr->vec_v, ray_ptr->vec_w);
    printf("POV plan: u:|%f|%f|%f| v:|%f|%f|%f| w:|%f|%f|%f|\n", ray_ptr->vec_u[0], ray_ptr->vec_u[1], ray_ptr->vec_u[2], \
    ray_ptr->vec_v[0], ray_ptr->vec_v[1], ray_ptr->vec_v[2], ray_ptr->vec_w[0], ray_ptr->vec_w[1], ray_ptr->vec_w[2]);
}

int
    ray_trace(t_param *p_ptr, t_pix_data *img_ptr)
{
    double      screen_dist;
    t_object    *cam_ptr;
    t_ray       *ray_ptr;
    int         i;
    int         x;
    int         y;

    cam_ptr = get_object(p_ptr->object, camera);
    screen_dist = (((double)p_ptr->res_x) / 2.0) / tan((((double)cam_ptr->fov) / 2.0) * M_PI / 180); /* Converting FOV to gradiants as this is what 'tan()' uses */
    if (!(ray_ptr = (t_ray *)malloc(sizeof(t_ray))))
        error_free(p_ptr, "Malloc error in 'shoot-ray'");
    i = 0;
    while (i < 3)
    {
        ray_ptr->origin[i] = cam_ptr->coord1[i]; /* Copying camera point of view */
        i++;
    }
    set_pov_plan(cam_ptr, ray_ptr);
    vec_scalar_product(ray_ptr->vec_w, screen_dist, 3); /* Computing direction vector as origin + (distance * direction(unitary)) */
    x = 0;
//    while(x < p_ptr->res_x)
    {
    //    printf("ray_x: |%f|\n", ray_ptr->direction[0]);
        vec_scalar_product(ray_ptr->vec_u, (((double)p_ptr->res_x) / 2.0) * -1.0 + (double)x, 3);
/*        ray_ptr->direction[0] = cam_ptr->coord2[0] * screen_dist \
        + (((double)p_ptr->res_x) / 2.0) * -1.0 + (double)x;
        printf("ray_x: |%f|%f|\n", ray_ptr->direction[0], (((double)p_ptr->res_x) / 2.0) * -1.0 + (double)x);
*/        y = 0;
//        while (y < p_ptr->res_y)
        {
//            printf("ray_y: |%f|\n", ray_ptr->direction[1]);
            vec_scalar_product(ray_ptr->vec_v, (((double)p_ptr->res_y) / 2.0) * -1.0 + (double)y, 3);
            vector_addition(ray_ptr->direction, ray_ptr->vec_u, ray_ptr->vec_v, 3);
            vector_addition(ray_ptr->direction, ray_ptr->direction, ray_ptr->vec_w, 3);
/*            ray_ptr->direction[1] = cam_ptr->coord2[1] * screen_dist + \
            ((((double)p_ptr->res_y) / 2.0) * -1 + (double)y);
            printf("ray_y: |%f|%f|\n", ray_ptr->direction[1], (((double)p_ptr->res_y) / 2.0) * -1.0 + (double)y);
*/
            if (shoot_ray(p_ptr, ray_ptr) >= 0.0)
                my_mlx_pixel_put(img_ptr, x, p_ptr->res_y - y, 0x00FF00FF);
            else
                my_mlx_pixel_put(img_ptr, x, p_ptr->res_y - y, p_ptr->light_rgb);
            y++;
        }
        x++;
    }
        printf("Origin: |%f|%f|%f|\n", ray_ptr->origin[0], ray_ptr->origin[1], ray_ptr->origin[2]);
        printf("Direction: |%f|%f|%f|\n", ray_ptr->direction[0], ray_ptr->direction[1], ray_ptr->direction[2]);
        printf("Distance: |%f|%f|%f|\n", screen_dist, (double)cam_ptr->fov / 2.0, tan(((double)cam_ptr->fov / 2.0) * M_PI / 180));

    free(ray_ptr);
    return (x + y);
}