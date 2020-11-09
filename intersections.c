#include "parsing/minirt.h"

double
    sphere_intersect(t_ray *ray_ptr, t_object *sphere)
{
    t_quadratic quad_params;
    double      temp_vec[3];

    quad_params.a = dot_product(ray_ptr->direction, ray_ptr->direction, 3);
    vector_substraction(temp_vec, ray_ptr->origin, sphere->coord1, 3); /* (e - c) */
    quad_params.b = 2.0 * dot_product(ray_ptr->direction, temp_vec, 3); /* 2d.(e-c) */
    quad_params.c = dot_product(temp_vec, temp_vec, 3) - pow((sphere->diameter / 2.0), 2);
    quad_params.discrim = pow(quad_params.b, 2) - 4 * quad_params.a * quad_params.c;
    if (quad_params.discrim < 0.0)
        return (-1.0);
    else if (quad_params.discrim == 0)
        return (-quad_params.b / (2 * quad_params.a));
    else
    {
        quad_params.solut_1 = (-quad_params.b - sqrt(quad_params.discrim)) / (2 * quad_params.a);
        quad_params.solut_2 = (-quad_params.b + sqrt(quad_params.discrim)) / (2 * quad_params.a);
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
    return (intersect);
}

double
    plane_intersect(t_ray *ray_ptr, t_object *plane_ptr)
{
    return (get_plane_intersect(ray_ptr, plane_ptr->coord1, plane_ptr->coord2));
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
        vector_substraction(sq_to_inter, ray_plane, square_ptr->coord1, 3);
        if ((length = vector_magnitude(sq_to_inter, 3)) > sqrt(pow(square_ptr->height / 2, 2) * 2)) //Optimization: exits if point is further than half a diagonal away
            return (0.0);
        if (length == 0.0)
            return (plane_inter);
        vec_normalize(sq_to_inter, 3);
        set_pov_plan(square_ptr->coord2, &tmp_pov);
        // print_vec(tmp_pov.vec_u);
        // print_vec(tmp_pov.vec_v);
        if ((tmp_val = fabs(dot_product(tmp_pov.vec_u, sq_to_inter, 3))) <= ((cos(45.0 / 180.0 * M_PI))))
        {
            // printf("Using v\t");
            // printf("")
            tmp_val = fabs(dot_product(tmp_pov.vec_v, sq_to_inter, 3));
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
