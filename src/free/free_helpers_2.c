#include "../../inc/minishell.h"

void	free_str_arr_null(char ***arr)
{
	free_str_arr(*arr);
	*arr = NULL;
}

void	free_env(t_env *env)
{
	free_str_arr_null(&env->key);
	free_str_arr_null(&env->value);
	free(env);
}
