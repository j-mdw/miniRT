#include "minirt.h"

void    del_all_elem(t_elem *elem)
{
    t_elem  *store;

    while(elem)
    {
        store = elem->next_elem;
        elem = elem->next_elem;
        free(store);
    }
}

void    free_all(t_param *param)
{
    int i;

    if (param->line)
        free(param->line);
    i = 0;
    if (param->line_split)
    {
        while (param->line_split[i])
        {
            free(param->line_split[i]);
            i++;
        }
        free(param->line_split);
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