#include "minirt.h"

void    del_all_elem(t_elem *elem)
{
    t_elem  *store;
    int i = 0; /* For debugging purposes, remove at end */

    while(elem)
    {
        store = elem;
        elem = elem->next_elem;
        free(store);
        i++;
        printf("Element |%d| freed", i);
    }
}

void    free_all(t_param *param)
{
    int i;

    if (param->line)
    {
        printf("Really?");
        free(param->line);
        printf("Parameter 'Line' freed\n");
    }
    i = 0;
    if (param->line_split)
    {
        while (param->line_split[i])
        {
            free(param->line_split[i]);
            printf("Line split element |%d| freed\n", i);
            i++;
        }
        free(param->line_split);
        printf("Parameter 'Line split' freed\n");
    }
    if (param->elem)
        del_all_elem(param->elem);
    printf("ALL FREED\n");
}

void    error_free(t_param *param, char *error_message)
{
    printf("%s\n", error_message);
    if (param->line)
        printf("ERROR: %s\n", param->line);
    free_all(param);
    exit(1);
}