#include "../minirt.h"

void
    vec_scalarprod(double *vector, double scalar, int dimension)
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
    dot_prod(double *vec1, double *vec2, int dimension)
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
    vec_addition(double *result, double *vec1, double *vec2, int dimension)
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
    vec_substract(double *result, double *vec1, double *vec2, int dimension)
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
    vec_magnit(double *vec, int dimension)
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