#include "minirt.h"

void    get_id(t_param *param_ptr)
{
    
    if (!ft_strcmp(*param_ptr->line_split, "R"))
        printf("R found");
    else
        error_free(param_ptr, "Incorrect identifier");
}

int     parse_params(t_param *param_ptr, int fd)
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
