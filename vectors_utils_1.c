#include "parsing/minirt.h"

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