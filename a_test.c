#include <stdio.h>

void
    cross_product(double *dst, double *vec1, double *vec2)
{
    dst[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
    dst[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
    dst[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
}

int main(void)
{
    double vec_u[3];
    double vev_v[] = {0.0, 1.0, 0.0};
    double vec_w[] = {0.0, 0.0, 1.0};

    cross_product(vec_u, vev_v, vec_w);
    printf("Vec u: |%f|%f|%f|\n", vec_u[0], vec_u[1], vec_u[2]);
    return (0);
}