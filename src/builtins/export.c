#include "../../inc/minishell.h"

char	export(t_env *env, char *key, char *value, char *arg)
{
	int	i;

	if (arg)
	{
		if (value && env_add(env, key, value))
			return (EXIT_FAILURE);
		else if (env_add(env, key, ft_strdup("")))
			return (EXIT_FAILURE);
/*
		if (env_sort(env))
			return (EXIT_FAILURE);
*/
	}
	i = -1;
	while (++i < env->len)
	{
		if (env->value[0])
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			ft_printf("declare -x %s\n", env->key);
	}
	return (EXIT_SUCCESS);
}
