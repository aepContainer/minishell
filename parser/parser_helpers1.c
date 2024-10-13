#include "parser.h"

int	str_arr_len(char **strarr)
{
    int i;

    i = 0;
    while (strarr[i])
        i++;
    return (i);
}

char	inject_char_to_str(char **str_p, char c)
{
	char	*temp;
	int		i;

	if (!str_p)
		return (-1);
	if (!*str_p)
	{
		temp = ft_calloc(1, 2);
		if (!temp)
			return (-1);
		temp[0] = c;
		*str_p = temp;
		return (0);
	}
	i = ft_strlen(*str_p);
	temp = ft_calloc(1, i + 2);
	if (!temp)
		return (-1);
	i = -1;
	while ((*str_p)[++i])
		temp[i] = (*str_p)[i];
	temp[i] = c;
	free(*str_p);
	*str_p = temp;
	return (0);
}

char	inject_str_to_arr(char ***str_arr_p, char *element)
{
	char	**temp;
	int		i;

	if (!str_arr_p)
		return (-1);
	if (!*str_arr_p)
	{
		temp = ft_calloc(2, sizeof(char *));
		if (!temp)
			return (-1);
		temp[0] = element;
		*str_arr_p = temp;
		return (0);
	}
	i = str_arr_len(*str_arr_p);
	temp = ft_calloc(sizeof (char *), i + 2);
	if (!temp)
		return (-1);
	i = -1;
	while ((*str_arr_p)[++i])
		temp[i] = (*str_arr_p)[i];
	temp[i] = element;
	free_str_arr(*str_arr_p);
	*str_arr_p = temp;
	return (0);
}
