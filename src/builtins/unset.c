#include "../../inc/parser.h"

char	unset(t_env **env, char *key)
{
	char	*value;

	if (!*env)
		return (EXIT_FAILURE);
	if (!key)
		return (EXIT_SUCCESS);
	value = env_find_value(*env, key);
	if (!value)
		return (EXIT_SUCCESS);
	return (env_del_element(env, key, value));
}
