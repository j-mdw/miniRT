#include "minirt.h"

#define	FILE_EXTANSION	".rt"
#define	FLAG "--save"


void	param_struct_init(t_param *param_ptr)
{
	param_ptr->save = 0;
	param_ptr->res_found = 0;
	param_ptr->amb_light_found = 0;
	param_ptr->line = NULL;
	param_ptr->line_split = NULL;
	param_ptr->elem = NULL;
	param_ptr->extra_split = NULL;
}

int	main(int argc, char **argv)
{
	int			fd;
	t_param		params;

	param_struct_init(&params);
	/* Checking for Flag and ensuring proper number of arguments are used */
	if (argc != 2)
	{
		if (argc == 3 && !(ft_strcmp(argv[2], FLAG)))
			params.save = 1;
		else
		{
			ft_putstr_fd("Incorrect number of arguments", 1);
			return (-1);
		}
	}
	params.light_ratio = 1.0; /* Useless, just to avoid errors at compile for now */
	params.light_ratio += 1.0; /* Same */
	if (!check_file_extansion(argv[1], FILE_EXTANSION))
	{
		ft_putstr_fd("Incorrect file extansion", 1);
		return (-1);
	}
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Failed opening the file, please make sure the file exists\n", 1);
		return (-1);
	}
	ft_putstr_fd("File Open\n", 1);
	parse_params(&params, fd);
	printf("Resoultion parameters: |x: %d|y: %d|\n", params.res_x, params.res_y);
	printf("Light ratio: %f\n", params.light_ratio);
	printf("Light RGB is: %#x\n", params.light_rgb);
	free_all(&params);
	return (0);
}
