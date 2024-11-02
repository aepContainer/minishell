#include "../../inc/minishell.h"

static char	calloc_key_value(char ***key, char ***value, int len)
{
	*key = ft_calloc(len, sizeof(char *));
	if (!*key)
		return (EXIT_FAILURE);
	*value = ft_calloc(len, sizeof(char *));
	if (!*value)
		return (free(*key), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	env_del_index(t_env **env, int index)
{
	t_env	*temp;
	char	state;
	int		i;

	temp = ft_calloc(1, sizeof(t_env));
	if (!temp)
		return (EXIT_FAILURE);
	temp->len = (*env)->len - 1;
	if (calloc_key_value(&temp->key, &temp->value, temp->len + 1))
		return (EXIT_FAILURE);
	state = 0;
	i = -1;
	while (++i < temp->len)
	{
		if (i == index)
		{
			state = 1;
			free((*env)->key);
			free((*env)->value);
		}
		temp->key[i] = (*env)->key[i + state];
		temp->value[i] = (*env)->value[i + state];
	}
	return (EXIT_SUCCESS);
}

char	env_del_element(t_env **env, char *key, char *value)
{
	t_env	*temp;
	int		len1;
	int		len2;
	int		i;

	if (!key || !value)
		return (EXIT_FAILURE);
	len1 = ft_strlen(key);
	temp = *env;
	i = -1;
	while (temp->key[++i])
	{
		len2 = ft_strlen(temp->key[i]);
		if (len1 == len2 && !ft_strncmp(temp->key[i], key, len1))
		{
			len2 = ft_strlen(temp->value[i]);
			if (ft_strlen(value) == len2 && ft_strncmp(temp->value[i], value, len2))
				return (env_del_index(env, i));
		}
	}
	return (EXIT_FAILURE);
}

char	env_add(t_env **env, char *key, char *value)
{
	t_env	*temp;
	int		i;

	if (!key || !value)
		return (EXIT_FAILURE);
	temp = ft_calloc(1, sizeof(t_env));
	if (!temp)
		return (EXIT_FAILURE);
	i = -1;
	temp->len = (*env)->len + 1;
	if (calloc_key_value(&temp->key, &temp->value, temp->len + 1))
		return (free(temp), EXIT_FAILURE);
	while (++i < temp->len)
	{
		temp->key[i] = (*env)->key[i];
		temp->value[i] = (*env)->value[i];
	}
	temp->key[i] = key;
	temp->value[i] = value;
	*env = temp;
	return (EXIT_SUCCESS);
}

char	*env_find_value(t_env *env, char *key)
{
	int	key_len;
	int	i;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = -1;
	while (env->key[++i])
	{
		if (ft_strlen(env->key[i]) == key_len && !ft_strncmp(env->key[i], key, key_len))
			return (env->value[i]);
	}
	return (NULL);
}
