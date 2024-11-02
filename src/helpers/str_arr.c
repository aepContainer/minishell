#include "../../inc/minishell.h"

int	str_arr_len(char **arr)
{
    int	i;

	i = 0;
    while (arr[i])
        i++;
    return (i);
}

char	**str_arr_realloc(char **arr, char *element)
{
    char	**rtrn;
    int		i;

    if (!arr)
    {
		rtrn = ft_calloc(2, sizeof(char *));
        if (!rtrn)
            return (NULL);
        rtrn[0] = ft_strdup(element);
        return (free(element), rtrn);
    }
	rtrn = ft_calloc(sizeof(char *), str_arr_len(arr) + 2);
	i = -1;
    if (!rtrn)
        return (NULL);
    while (arr[++i])
    {
        rtrn[i] = ft_strdup(arr[i]);
        free(arr[i]);
    }
    rtrn[i] = ft_strdup(element);
    return (free(arr), free(element), rtrn);
}
