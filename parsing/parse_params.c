#include "minirt.h"

/*
void
    get_coordinates(t_param *param_ptr);
*/
/* Checks if a string is of form "digits.digit", and then converts it to float */


void
    parse_resolution(t_param *param_ptr)
{       
    printf("R found\n"); /* TBR */
    if (param_ptr->res_found)
        error_free(param_ptr, "Resolution provided multiple times");
    else
        param_ptr->res_found = 1;
    if (array_size(param_ptr->line_split) != 3)
        error_free(param_ptr, "Incorrect number of arguments for Resolution");
    else
    {
        if (ft_isnumber(param_ptr->line_split[1]))
            param_ptr->res_x = ft_atoi(param_ptr->line_split[1]);
        else
            error_free(param_ptr, "Incorrect 'x' resolution value");
        if (ft_isnumber(param_ptr->line_split[2]))
            param_ptr->res_y = ft_atoi(param_ptr->line_split[2]);
        else
            error_free(param_ptr, "Incorrect 'y' resolution value");
    }
}

void
    parse_light(t_param *param_ptr)
{
    printf("A found\n"); /* TBR */
    if (param_ptr->amb_light_found)
        error_free(param_ptr, "Ambiant light provided multiple times");
    else
        param_ptr->amb_light_found = 1;
    if (array_size(param_ptr->line_split) != 3)
        error_free(param_ptr, "Incorrect number of arguments for Ambiant light");
    else
    {
        param_ptr->light_ratio = atoitof(param_ptr, param_ptr->line_split[1]);
        if (param_ptr->light_ratio > 1.0 || param_ptr->light_ratio < 0.0)
            error_free(param_ptr, "Incorrect light ratio, make sure it is between 0.0 and 1.0");
        param_ptr->light_rgb = get_rgb(param_ptr, param_ptr->line_split[2]);
    }
}

void
	parse_camera(t_param *param_ptr)
{
    t_camera    *cam_ptr;
    int         i;

	if (array_size(param_ptr->line_split) != 4)
		error_free(param_ptr, "Incorrect number of arguments for Camera");
	add_new_elem_front(param_ptr);
	param_ptr->elem->id = camera;
    cam_ptr = (t_camera *)malloc(sizeof(t_camera));
	param_ptr->elem->object = cam_ptr;
    get_coord(param_ptr->line_split[1], cam_ptr->coord, param_ptr, 3);
    get_coord(param_ptr->line_split[2], cam_ptr->orient, param_ptr, 3);
    i = 0;
    while (i < 3)
    {
        if (cam_ptr->orient[i] < -1.0 || cam_ptr->orient[i] > 1.0)
            error_free(param_ptr, "Orientation vector values out of [-1,1] range");  
        i++;
    }
    if ((ft_isnumber(param_ptr->line_split[3])))
    {
        cam_ptr->fov = ft_atoi(param_ptr->line_split[3]);
        if (cam_ptr->fov < 0 || cam_ptr->fov >180)
            error_free(param_ptr, "Camera FOV not in range [0,180]");
    }
    else
        error_free(param_ptr, "Camera FOV not a number");
}

void
    get_id(t_param *param_ptr)
{ 
    if (!ft_strcmp(*param_ptr->line_split, "R"))
        parse_resolution(param_ptr);
    else if (!ft_strcmp(*param_ptr->line_split, "A"))
        parse_light(param_ptr);
	else if (!ft_strcmp(*param_ptr->line_split, "c"))
	    parse_camera(param_ptr);
    else
        error_free(param_ptr, "Incorrect identifier (from Get_ID)");
}

int
    parse_params(t_param *param_ptr, int fd)
{
    int gnl;

    while ((gnl = get_next_line(fd, &param_ptr->line)) > 0)  
    {
        printf("Line: %s\n", param_ptr->line);
        replace_char(param_ptr->line, '\t', ' ');
        if (param_ptr->line[0]) /* Checking if line is not '\0' which corresponds to an empty line in the file */
        {
            if (!(param_ptr->line_split = ft_split(param_ptr->line, ' ')))
                error_free(param_ptr, "Split Error");
            if ((param_ptr->line_split[0])) /* Checking if *line_split != NULL - this would happen if line was only white spaces */
                get_id(param_ptr);
        }
        if (param_ptr->line_split)
            free_2D_array(&param_ptr->line_split);
        free(param_ptr->line);
    }
    printf("GNL RETURN: %d\n", gnl);
    return (1);
}
