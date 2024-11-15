#include "../../inc/minishell.h"

void	env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->len)
	{
		write(1, env->key[i], ft_strlen(env->key[i]));
		write(1, "=", 1);
        write(1, env->value[i], ft_strlen(env->value[i]));
        write(1, "\n", 1);
		i++;
	}
}
