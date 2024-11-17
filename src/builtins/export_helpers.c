#include "../../inc/minishell.h"

char	update_env(t_env *env, char *key, char *value)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = -1;
	while (env->key[++i])
	{
		if (!ft_strncmp(env->key[i], key, key_len)
				&& key_len == ft_strlen(env->key[i]))
		{
			free(env->value[i]);
			env->value[i] = ft_strdup(value);
			if (!env->value[i])
				return (-1);
			free(value);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
