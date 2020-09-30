#include "minirt.h"

void
    add_new_elem_front(t_param *param_ptr)
{/*
	t_elem *new_elem;

	if (!(new_elem = (t_elem *)malloc(sizeof(t_elem))))
        error_free(param_ptr, "New element malloc error");
    new_elem->next_elem = param_ptr->elem;
    param_ptr->elem = new_elem;
*/
    t_object *new_obj;

	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
        error_free(param_ptr, "New element malloc error");
    new_obj->next_object = param_ptr->object;
    param_ptr->object = new_obj;
}