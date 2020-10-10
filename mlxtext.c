#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include <stdio.h>

typedef struct s_pix_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_pix_data;

void            my_mlx_pixel_put(t_pix_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_pix_data	img;

	if(!(mlx = mlx_init()))
	{
		printf("we have a pbm...");
		return (0);
	}
	printf("Success!");
	mlx_win = mlx_new_window(mlx, 400, 400, "hello world");
	img.img = mlx_new_image(mlx, 400, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i = 0;
	int j = 0;
	while (i < 400)
	{
		while (j < 400 )
		{
			my_mlx_pixel_put(&img, i, j, 0xAFFFF6A0);
			j++;
		}
		j = 0;
		i++;
	}
	
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
