#include "minirt.h"

int
    ft_isnumber(char *s)
{
    while (ft_isdigit(*s))
        s++;
    if (*s == '\0')
        return (1);
    return (0);
}

int
    array_size(char **arr_ptr)
{
    int i;

    i = 0;
    while (arr_ptr[i])
        i++;
    return (i);
}
/*
void
    get_rgb(t_param *param_ptr)
{

    }

void
    get_coordinates(t_param *param_ptr);
*/
/* Checks if a string is of form "digits.digit", then converts it to float */

float   atoitof(t_param *param_ptr, char *s)
{
    int result;
    int i;

    i = 0;
    while (ft_isdigit(s[i]))
        i++;
    if (s[i] == '.' && ft_isdigit(s[i + 1]) && s[i + 2] == '\0')
    {
        result = ft_atoi(s);
        result = result * 10 + s[i + 1] - '0';
        return (((float)result) / 10);
    }
    else
    {
        error_free(param_ptr, "Wrong format of floating point value");
        return (0.0f);
    }
}

void
    parse_resolution(t_param *param_ptr)
{
    if (array_size(param_ptr->line_split) != 3)
        error_free(param_ptr, "Incorrect number of arguments on line");
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
    if (array_size(param_ptr->line_split) != 3)
        error_free(param_ptr, "Incorrect number of arguments");
    else
    {
        param_ptr->light_ratio = atoitof(param_ptr, param_ptr->line_split[1]);
        if (param_ptr->light_ratio > 1.0 || param_ptr->light_ratio < 0.0)
            error_free(param_ptr, "Incorrect light ratio, make sure it is between 0.0 and 1.0");
        param_ptr->light_rgb = get_rgb(param_ptr, param_ptr->line_split[2]);
    }
}

void
    get_id(t_param *param_ptr)
{
    
    if (!ft_strcmp(*param_ptr->line_split, "R"))
    {
        printf("R found");
        parse_resolution(param_ptr);
    }
    if (!ft_strcmp(*param_ptr->line_split, "A"))
    {
        printf("A found");
        parse_light(param_ptr);
    }
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
    }
    printf("GNL RETURN: %d\n", gnl);
    return (1);
}
