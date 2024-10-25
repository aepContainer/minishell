#include "../../inc/parser.h"

int	str_arr_len(char **arr)
{
    int	i = 0;
    while (arr[i])
        i++;
    return (i);
}

char	**str_arr_realloc(char **arr, char *element)
{
    char	**rtrn;
    int	i = -1;

    if (!arr)
    {
        if (!(rtrn = ft_calloc(sizeof(char *), 2)))
            return (NULL);
        rtrn[0] = ft_strdup(element);
        return (free(element), rtrn);
    }
    if (!(rtrn = ft_calloc(sizeof(char *), str_arr_len(arr) + 2)))
        return (NULL);
    while (arr[++i])
    {
        rtrn[i] = ft_strdup(arr[i]);
        free(arr[i]);
    }
    rtrn[i] = ft_strdup(element);
    return (free(arr), free(element), rtrn);
}
