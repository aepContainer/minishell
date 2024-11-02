#include "../../inc/minishell.h"

static void	free_key_value(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
}

void	free_env_node(t_env *env)
{
	free_key_value(env);
	free(env);
}
