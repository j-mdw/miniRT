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
//         vec_copy(ray_ptr->direction, ray_plane, 3);
//         vec_scalarprod(ray_plane, tmp_val, 3);
//         vec_addition(ray_plane, ray_plane, ray_ptr->origin, 3);
//         vec_substract(sq_to_inter, ray_plane, square_ptr->coord1, 3);
//         // printf("Length: %f, Height: %f, max length: %f\n", vec_magnit(sq_to_inter, 3), square_ptr->height, sqrt(pow(square_ptr->height / 2, 2) * 2));
//         if (vec_magnit(sq_to_inter, 3) <= sqrt(pow(square_ptr->height / 2, 2) * 2))
//         {
//             // printf("Center to intersection distance: %f\n", vec_magnit(sq_to_inter, 3));
//             return (tmp_val);
//         }
//     }
//     return (0.0);
// }