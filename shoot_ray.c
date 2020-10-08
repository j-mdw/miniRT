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


int
    shoot_ray(t_ray *ray_ptr, int x, int y)
{

}


int
    ray_trace(t_param *p_ptr)
{
    double      screen_dist;
    t_object    *view_point;
    t_ray       *ray;
    int         i;
    int         x;
    int         y;

    view_point = get_object(p_ptr->object, camera);
    screen_dist = (((double)p_ptr->res_x) / 2.0) / tan(((double)view_point->fov / 2.0) * M_PI / 180); /* Converting FOV to gradiants as this is what 'tan()' uses */
    if (!(ray = (t_ray *)malloc(sizeof(t_ray))))
        error_free(p_ptr, "Malloc error in 'shoot-ray'");
    i = 0;
    while (i < 3)
    {
        ray->origin[i] = view_point->coord1[i]; /* Copying camera point of view */
        ray->direction[i] = view_point->coord1[i] + view_point->coord2[i] * screen_dist; /* Computing direction vector as origin + (distance * direction(unitary)) */
        i++;
    }
    x = 0;
    
    while(x < p_ptr->res_x)
    {
        y = 0;
        while (y < p_ptr->res_y)
        {
            shoot_ray(ray, x, y);
            y++;
        }
        x++;
    }
        printf("Origin: |%f|%f|%f|\n", ray->origin[0], ray->origin[1], ray->origin[2]);
        printf("Direction: |%f|%f|%f|\n", ray->direction[0], ray->direction[1], ray->direction[2]);
        printf("Distance: |%f|%f|%f|\n", screen_dist, (double)view_point->fov / 2.0, tan(((double)view_point->fov / 2.0) * M_PI / 180));
        free(ray);
    return (x + y);
}