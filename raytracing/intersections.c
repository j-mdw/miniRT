#include "../minirt.h"

double
    sphere_intersect(t_ray *ray_ptr, t_object *sphere)
{
    t_quadratic q_param;
    double      temp_vec[3];

    q_param.a = dot_prod(ray_ptr->direction, ray_ptr->direction, 3);
    vec_substract(temp_vec, ray_ptr->origin, sphere->coord1, 3);
    q_param.b = 2.0 * dot_prod(ray_ptr->direction, temp_vec, 3);
    q_param.c = dot_prod(temp_vec, temp_vec, 3) - pow((sphere->diameter / 2.0), 2);
    q_param.discrim = pow(q_param.b, 2) - 4 * q_param.a * q_param.c;
    if (q_param.discrim < 0.0)
        return (-1.0);
    else if (q_param.discrim == 0)
        return (-q_param.b / (2 * q_param.a));
    else
    {
        q_param.solut_1 = (-q_param.b - sqrt(q_param.discrim)) / (2 * q_param.a);
        q_param.solut_2 = (-q_param.b + sqrt(q_param.discrim)) / (2 * q_param.a);
        if (q_param.solut_1 < q_param.solut_2)
            return (q_param.solut_1);
        return (q_param.solut_2);
    }
}

double
    get_plane_intersect(t_ray *ray_ptr, double *plane_origin, double *plane_n)
{
    double  intersect;
    double  tmp_val;
    double  tmp_vec[3];

    if ((tmp_val = dot_prod(ray_ptr->direction, plane_n, 3)) == 0.0)
        return(0.0);
    vec_substract(tmp_vec, plane_origin, ray_ptr->origin, 3);
    intersect = dot_prod(tmp_vec, plane_n, 3) / tmp_val;
    return (intersect);
}

double
    plane_intersect(t_ray *ray_ptr, t_object *plane_ptr)
{
    return (get_plane_intersect(ray_ptr, plane_ptr->coord1, plane_ptr->coord2));
}

void
    print_vec(double *vec)
{
    int i = 0;

    while (i < 3)
    {
        printf("|%.4f|", vec[i]);
        i++;
    }
    printf("\n");
}

double
    square_intersect(t_ray *ray_ptr, t_object *square_ptr)
{
    double  ray_plane[3];
    double  sq_to_inter[3];
    double  plane_inter;
    double  tmp_val;
    double  length;
    t_ray   tmp_pov;

    if ((plane_inter = get_plane_intersect(ray_ptr, square_ptr->coord1, square_ptr->coord2)) > JEAN)
    {
        vector_copy(ray_ptr->direction, ray_plane, 3);
        vec_scalar_product(ray_plane, plane_inter, 3);
        vector_addition(ray_plane, ray_plane, ray_ptr->origin, 3);
        vec_substract(sq_to_inter, ray_plane, square_ptr->coord1, 3);
        if ((length = vector_magnitude(sq_to_inter, 3)) > sqrt(pow(square_ptr->height / 2, 2) * 2)) //Optimization: exits if point is further than half a diagonal away
            return (0.0);
        if (length == 0.0)
            return (plane_inter);
        vec_normalize(sq_to_inter, 3);
        set_pov_plan(square_ptr->coord2, &tmp_pov);
        // print_vec(tmp_pov.vec_u);
        // print_vec(tmp_pov.vec_v);
        if ((tmp_val = fabs(dot_prod(tmp_pov.vec_u, sq_to_inter, 3))) <= ((cos(45.0 / 180.0 * M_PI))))
        {
            // printf("Using v\t");
            // printf("")
            tmp_val = fabs(dot_prod(tmp_pov.vec_v, sq_to_inter, 3));
        }
        // printf("Angle: %f\n", tmp_val);
        tmp_val = (square_ptr->height / 2) / tmp_val;
        // printf("Pd/Sd: |%f|%f|\n", tmp_val, length);
        if (length < tmp_val)
        {
            return (plane_inter);

        }

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

    vec_substract(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
    vec_substract(tmp_vec2, tri_ptr->coord3, tri_ptr->coord2, 3);
    cross_product(tri_n, tmp_vec1, tmp_vec2);
    vec_normalize(tri_n, 3);
    if (dot_prod(tri_n, ray_ptr->direction, 3) > 0.0)
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
    vec_substract(tmp_vec1, tri_ptr->coord2, tri_ptr->coord1, 3);
    vec_substract(tmp_vec2, point_inter, tri_ptr->coord1, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 1: %f\n", dot_prod(tri_n, tmp_vec3, 3));
    sum_check = 0;
    if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;
    vec_substract(tmp_vec1, tri_ptr->coord3, tri_ptr->coord2, 3);
    vec_substract(tmp_vec2, point_inter, tri_ptr->coord2, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 2: %f\n", dot_prod(tri_n, tmp_vec3, 3));
    if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;
    vec_substract(tmp_vec1, tri_ptr->coord1, tri_ptr->coord3, 3);
    vec_substract(tmp_vec2, point_inter, tri_ptr->coord3, 3);
    cross_product(tmp_vec3, tmp_vec1, tmp_vec2);
    // printf("Dot 3: %f\n", dot_prod(tri_n, tmp_vec3, 3));
    if (dot_prod(tri_n, tmp_vec3, 3) < 0.0)
        sum_check += 1;
    if (sum_check == 3 || sum_check == 0)
    {
        // printf("### WINWINWINWIN ###\n");
        return (plane_dist);
    }
    return (0.0);
}

/*
*   Parameters:
*   - Ro : ray origin
*   - Rd : ray direction
*   - Co : cylinder origin
*   - Cn : cylinder normal
*   - r  : Ray
*
*   Formula: (P - Co - (Cn . (P - Co)*Cn))^2 - r^2 = 0
*   Where P is the point on the cylinder. Replace P by Ro + Rd*t and simplify to get quad terms
*   a = (Rd - (Rd . Cn)*Cn)^2
*   b = 2 * ((Rd - (Rd . Cn)*Cn) . ((Ro - Co) - ((Ro - Co).Cn)*Cn))
*   c = ((Ro - Co) - ((Ro - Co).Cn)*Cn)^2 - r^2
*/
double
    cylinder_intersect(t_ray *ray_ptr, t_object *cy_ptr)
{
    t_quadratic q_param;
    double      tmp_vec1[3];
    double      tmp_vec2[3];
    double      co_to_ro[3];

    vector_copy(cy_ptr->coord2, tmp_vec1, 3);
    vec_scalar_product(tmp_vec1, dot_prod(ray_ptr->direction, cy_ptr->coord2, 3), 3);
    vec_substract(tmp_vec1, ray_ptr->direction, tmp_vec1, 3);
    q_param.a = dot_prod(tmp_vec1, tmp_vec1, 3);

    vec_substract(co_to_ro, ray_ptr->origin, cy_ptr->coord1, 3);
    vector_copy(cy_ptr->coord2, tmp_vec2, 3);
    vec_scalar_product(tmp_vec2, dot_prod(co_to_ro, tmp_vec2, 3), 3);
    vec_substract(tmp_vec2, co_to_ro, tmp_vec2, 3);
    q_param.b = 2 * dot_prod(tmp_vec1, tmp_vec2, 3);
    q_param.c = dot_prod(tmp_vec2, tmp_vec2, 3) - pow(cy_ptr->diameter / 2, 2);

    q_param.discrim = pow(q_param.b, 2) - 4 * q_param.a * q_param.c;
    if (q_param.discrim < 0.0)
        return (0.0);
    else if (q_param.discrim == 0)
        return (-q_param.b / (2 * q_param.a));
    else
    {
        q_param.solut_1 = (-q_param.b - sqrt(q_param.discrim)) / (2 * q_param.a);
        q_param.solut_2 = (-q_param.b + sqrt(q_param.discrim)) / (2 * q_param.a);
        if (pow(q_param.solut_1, 2) < pow(q_param.solut_2, 2)) //Not sure this is fine, negative would be behind the camera I think (but then could I get negative values?? considering the vector direction that woud probably not happen?)
            return (q_param.solut_1);
        return (q_param.solut_2);
    }
}