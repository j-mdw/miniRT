#include "minirt.h"

void    del_all_elem(t_object *object_ptr)
{
    t_object  *store;
    int i = 0; /* For debugging purposes, remove at end */

    while(object_ptr)
    {
        store = object_ptr;
        object_ptr = object_ptr->next_object;
        free(store);
        i++;
        printf("Element |%d| freed\t", i);
    }
}

void    free_2D_array(char ***ptr)
{
    int i;

    i = 0;
    while ((*ptr)[i])
    {
        free((*ptr)[i]);
        i++;
    }
    free(*ptr);
    *ptr = NULL;
}

void    free_all(t_param *param)
{
    if (param->line)
    {
        printf("There is a line, the line is: |%s|\n", param->line);
        free(param->line);
        printf("Parameter 'Line' freed\n");
    }
    if (param->line_split)
    {
        free_2D_array(&(param->line_split));
        printf("Line split freed\n");
    }
    if (param->extra_split)
    {
        free_2D_array(&(param->extra_split));
        printf("Extra split freed\n");
    }
    if (param->object)
        del_all_elem(param->object);
    printf("End of Free_All function\n");
}

void    error_free(t_param *param, char *error_message)
{
    printf("%s\n", error_message);
    if (param->line)
        printf("ERROR, line: %s\n", param->line);
    free_all(param);
    exit(1);
}