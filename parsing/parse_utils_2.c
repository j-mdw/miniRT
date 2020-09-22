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

int
    get_rgb(t_param *param_ptr, char *s)
{
    int     i;
    int     store;
    int     rgb;

    if (!(param_ptr->extra_split = ft_split(s, ',')))
        error_free(param_ptr, "Split error in get_rgb function");
    if (!(i = 0) && !(rgb = 0) && array_size(param_ptr->extra_split) != 3)
        error_free(param_ptr, "Incorrect number of RGB parameters");
    while (param_ptr->extra_split[i])
    {
        if (!(ft_isnumber(param_ptr->extra_split[i])))
            error_free(param_ptr, "Incorrect entries in rgb");
        else
        {
            store = ft_atoi(param_ptr->extra_split[i]);
            if (store >= 0 && store <= 255 && ++i)
            {
                rgb = rgb << 8;
                rgb += store;
            }
            else
                error_free(param_ptr, "RGB value out of 0-255 range");
        }
    }
    return(rgb);
}