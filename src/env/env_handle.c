#include "../../inc/parser.h"

char	env_del(t_env **env, char *key, char *value)
{
	t_env	**origin;
	t_env	*temp;
	int		len[2];

	if (!key || !value)
		return (EXIT_FAILURE);
	origin = env;
	temp = *env;
	while (*env)
	{
		len[0] = ft_strlen(temp->key);
		len[1] = ft_strlen(key);
		if (len[0] == len[1] && !ft_strncmp(temp->key, key, len[0]))
		{
			len[0] = ft_strlen(temp->value);
			len[1] = ft_strlen(value);
			if (len[0] == len[1] && !ft_strncmp(temp->value, value, len[0]))
			{
				*env = ((*env)->next);
				return (free_env_node(temp), EXIT_SUCCESS);
			}
		}
		temp = temp->next;
	}
	return (EXIT_FAILURE);
}

char	env_add(t_env *env, char *key, char *value)
{
	if (!key || !value)
		return (EXIT_FAILURE);
	while (env->next)
		env = env->next;
	env->next = ft_calloc(1, sizeof(t_env));
	if (!env->next)
		return (EXIT_FAILURE);
	env->next->key = key;
	env->next->value = value;
	return (EXIT_SUCCESS);
}
