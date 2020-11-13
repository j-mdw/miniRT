#include "../minirt.h"

void
	cross_product(double *dst, double *vec1, double *vec2)
{
	double	tmp_vec[3];

	tmp_vec[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
	tmp_vec[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
	tmp_vec[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
	dst[0] = tmp_vec[0];
	dst[1] = tmp_vec[1];
	dst[2] = tmp_vec[2];
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
	vec_copy(double *src, double *dst, int dimension)
{
	int i;

	i = 0;
	while (i < dimension)
	{
		dst[i] = src[i];
		i++;
	}
}

void
	vec_normalize(double *vec, int dimension)
{
	double	magnitude;

	magnitude = vec_magnit(vec, dimension);
	vec_scalarprod(vec, 1 / magnitude, dimension);
}
