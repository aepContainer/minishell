#include "../../inc/libft/libft.h"

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
		rtrn = ft_calloc(sizeof(char *), 2);
		if (!rtrn)
			return (NULL);
		rtrn[0] = ft_strdup(element);
		return (rtrn);
	}
	rtrn = ft_calloc(sizeof(char *), str_arr_len(arr) + 2);
	if (!rtrn)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		rtrn[i] = ft_strdup(arr[i]);
		free(arr[i]);
	}
	rtrn[i] = element;
	return (free(arr), rtrn);
}
