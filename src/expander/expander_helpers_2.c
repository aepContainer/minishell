#include "../../inc/minishell.h"

void	update_quote_state(t_quote_state *state, char c)
{
    if (c == '\'' && !state->in_double)
        state->in_single = !state->in_single;
    else if (c == '\"' && !state->in_single)
        state->in_double = !state->in_double;
}

char	*find_value(t_env *env, char *key_start, int key_len)
{
	char	*key;
	char	*value;

    if (!env || !key_start || !key_len)
	{
        return (NULL);
	}
	key = ft_substr(key_start, 0, key_len);
	if (!key)
	{
		return (NULL);
	}
	value = env_find_value(env, key);
	free(key);
	if (!value)
		return (NULL);
    return (value);
}
