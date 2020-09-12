#include "minirt.h"

#define	F_EXTANSION	".rt"
#define	FLAG "--save"

int	main(int argc, char **argv)
{
	int			fd;
	t_param		params;

	params.save = 0;
	params.line = NULL;
	params.line_split = NULL;
	params.elem = NULL;
	
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
	if (!check_file_extansion(argv[1], F_EXTANSION))
	{
		ft_putstr_fd("Incorrect file extansion", 1);
		return (-1);
	}
	if (!(fd = open(argv[1], O_RDONLY)))
	{
		ft_putstr_fd("Opening file failed, make sure file name is accurate\n", 1);
		return (-1);
	}
	ft_putstr_fd("File Open\n", 1);
	parse_params(&params, fd);
	free_all(&params);
	return (0);
}
