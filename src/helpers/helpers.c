#include "../../inc/minishell.h"

char	*env_find_value_const(t_env *env, const char *key)
{
	int	key_len;
	int	i;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = -1;
	while (env->key[++i])
	{
		if ((int) ft_strlen(env->key[i]) == key_len
				&& !ft_strncmp(env->key[i], key, key_len))
			return (env->value[i]);
	}
	return (NULL);
}

char	*ft_strjoin_const(char *s1, const char *s2)
{
	char	*dst;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	dst = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = -1;
	while (s2[++j])
		dst[i + j] = s2[j];
	dst[i + j] = 0;
	return (dst);
}

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
        return (rtrn);
    }
	rtrn = ft_calloc(sizeof(char *), str_arr_len(arr) + 2);
	i = -1;
    if (!rtrn)
        return (NULL);
    while (arr[++i])
        rtrn[i] = ft_strdup(arr[i]);
    rtrn[i] = ft_strdup(element);
    return (rtrn);
}
