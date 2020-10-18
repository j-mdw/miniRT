#include "parsing/minirt.h"

void
    cross_product(double *dst, double *vec1, double *vec2)
{
    dst[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
    dst[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
    dst[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
}

void
    vec_add_scalar(double *vec, double scalar, int dimension)
{
    int i;

    i = 0;
    while (i < dimension)
    {
        vec[i] += scalar;
        i++;
    }
}

void
    vector_copy(double *src, double *dst, int dimension)
{
    int i;

    i = 0;
    while (i < dimension)
    {
        dst[i] = src[i];
        i++;
    }
}