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
    return (rgb);
}

double
    max_d(double nb1, double nb2)
{
    if (nb1 > nb2)
        return (nb1);
    return (nb2);
}

/*
* ray_ptr->n_normal: unit vector perpendicular to the surface
* ray_ptr->l_light_src: unit vector pointing towards the light source
* v_cam_eye: unit vector pointing towards the eye of the camera
*
* Lambertian Shading: Pix_color = k(d) * I * max(0, n.l)
*   Where k(d) is the diffuse coefficient or the surface color
*   where I is the intensity of the light source
*
* Specular reflexion: Blinn-Phong shading
* Pixel color = lambertian shading + k(s) * I * max(0,n.h)^p
*   where p is the power of the shading: the greater it is, the faster the shininess will decrease
*   where k(s) is the specular coefficient or specular color of the surface (in doubt, make it grey with equal red, green, blue)
*   where h is (v + l) / ||v + l||
*/

double
    specular_reflexion(t_ray *ray_ptr, t_object *light_ptr)
{
    double  vec_h[3];
    double  spec_coeff = 0.5;

    vector_copy(ray_ptr->direction, ray_ptr->v_cam_eye, 3); /* Eventually, v_cam_eye and vec_h computation could  be done in get_color */
    vec_scalar_product(ray_ptr->v_cam_eye, (-1.0 / vector_magnitude(ray_ptr->v_cam_eye, 3)), 3);
    vector_addition(vec_h, ray_ptr->v_cam_eye, ray_ptr->l_light_src, 3);
    vec_scalar_product(vec_h, (1 / vector_magnitude(vec_h, 3)), 3);
    return (spec_coeff * light_ptr->brightness * pow(max_d(0.0, dot_product(ray_ptr->n_normal, vec_h, 3)), PHONG_EXPONENT));
}

int
    get_color(t_param *p_ptr, t_ray *ray_ptr, t_object *obj_ptr)
{
    double      rgb[3];
    t_object    *light_ptr;
    double      dot_l_n;
    int         i;

    light_ptr = p_ptr->object;
    vector_copy(ray_ptr->vec_intersect, ray_ptr->tmp_vec, 3);
    vec_scalar_product(ray_ptr->tmp_vec, -1.0, 3);
    // printf("vec_intersect * -1: %f|%f|%f|%f\n", ray_ptr->vec_intersect[0], ray_ptr->vec_intersect[1], ray_ptr->vec_intersect[2], vector_magnitude(ray_ptr->vec_intersect, 3));
    // while (light_ptr)
    // {
        while (light_ptr->obj_id != light)
            light_ptr = light_ptr->next_object;
        if (light_ptr->obj_id == light)
        {
            i = 0;
            while (i < 3)
            {
                ray_ptr->n_normal[i] = (ray_ptr->vec_intersect[i] - obj_ptr->coord1[i]) / (obj_ptr->diameter / 2);
                ray_ptr->l_light_src[i] = (light_ptr->coord1[i] - ray_ptr->vec_intersect[i]); /// dot_product(light_ptr->coord1, ray_ptr->tmp_vec, 3);
                i++;
            }
            vec_scalar_product(ray_ptr->l_light_src, (1 / vector_magnitude(ray_ptr->l_light_src, 3)), 3);
            // printf("ray_ptr->n_normal: %f|%f|%f|%f\n", ray_ptr->n_normal[0], ray_ptr->n_normal[1], ray_ptr->n_normal[2], vector_magnitude(ray_ptr->n_normal, 3));
            // printf("ray_ptr->l_light_src: %f|%f|%f|%f\n", ray_ptr->l_light_src[0], ray_ptr->l_light_src[1], ray_ptr->l_light_src[2], vector_magnitude(ray_ptr->l_light_src, 3));
            dot_l_n = max_d(0.0, dot_product(ray_ptr->n_normal, ray_ptr->l_light_src, 3));
            // printf("dot n.l: %f\n", dot_l_n);
            /*if (dot_l_n == 0.0)
                return (convert_rgb_format(p_ptr->light_rgb));  UNCOMMENT THIS ONCE FULLY FUNCTIONAL - USEFUL FOR DEBUGGING */  
            i = 0;
            while (i < 3)
            {
                rgb[i] = obj_ptr->rgb[i] * light_ptr->brightness * light_ptr->rgb[i] * dot_l_n + specular_reflexion(ray_ptr, light_ptr) \
                + (p_ptr->light_ratio * p_ptr->light_rgb[i]);
                if (rgb[i] > 1.0)
                    rgb[i] = 1.0;
                // printf("R then G then B: %f\n", rgb[i]);
                i++;
            }
            // printf("RGB convert: %#X\n", convert_rgb_format(rgb));
            return (convert_rgb_format(rgb)); 
        }
        // light_ptr = light_ptr->next_object;
    // }
    return (convert_rgb_format(p_ptr->light_rgb));     
}