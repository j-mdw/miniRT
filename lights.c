#include "parsing/minirt.h"

int
    convert_rgb_format(double *rgb_arr)
{
    int i;
    int rgb;

    i = 0;
    rgb = 0;
    while (i < 3)
    {
        rgb = (rgb << 8) + (unsigned int)(rgb_arr[i] * 255.0);
        i++;
    }
    // printf("RGB1: %f|%f|%f|%d\n", rgb_arr[0], rgb_arr[1], rgb_arr[2], rgb);
    return (rgb);
}

double
    max_d(double nb1, double nb2)
{
    if (nb1 > nb2)
        return (nb1);
    return (nb2);
}

int
    get_color(t_param *p_ptr, t_ray *ray_ptr, t_object *obj_ptr)
{
    double      vec_n[3];
    double      vec_l[3];
    double      tmp_vec[3];
    double      rgb[3];
    t_object    *light_ptr;
    double      dot_l_n;
    int         i;

    light_ptr = p_ptr->object;
    vector_copy(ray_ptr->vec_intersect, tmp_vec, 3);
    vec_scalar_product(tmp_vec, -1.0, 3);
    while (light_ptr)
    {
        if (light_ptr->obj_id == light)
        {
            i = 0;
            while (i < 3)
            {
                vec_n[i] = (ray_ptr->vec_intersect[i] - obj_ptr->coord1[i]) / (obj_ptr->diameter / 2);
                vec_l[i] = (light_ptr->coord1[i] - ray_ptr->vec_intersect[i]) / dot_product(light_ptr->coord1, tmp_vec,3);
                i++;
            }
            printf("vec_n: %f|%f|%f|%f\n", vec_n[0], vec_n[1], vec_n[2], vector_magnitude(vec_n, 3));
            printf("vec_l: %f|%f|%f|%f\n", vec_l[0], vec_l[1], vec_l[2], vector_magnitude(vec_l, 3));
            dot_l_n = max_d(0.0, dot_product(vec_n, vec_l, 3));
            printf("dot n.l: %f\n", dot_l_n);
            i = 0;
            while (i < 3)
            {
                rgb[i] = obj_ptr->rgb[i] * light_ptr->brightness * dot_l_n;
                i++;
            }
            return (convert_rgb_format(rgb)); 
        }
        light_ptr = light_ptr->next_object;
    }
    return (convert_rgb_format(p_ptr->light_rgb));     
}