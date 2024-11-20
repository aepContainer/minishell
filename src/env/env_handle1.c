/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:18 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:19 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
			return (env_del_index(env, i));
	}
	return (EXIT_SUCCESS);
}

char	env_add(t_env *env, char *key, char *value)
{
	env->key = str_arr_realloc(env->key, key);
	if (!env->key)
		return (EXIT_FAILURE);
	if (value)
	{
		env->value = str_arr_realloc(env->value, value);
		if (!env->value)
			return (EXIT_FAILURE);
	}
	else
	{
		value = ft_strdup("");
		if (!value)
			return (EXIT_FAILURE);
		env->value = str_arr_realloc(env->value, value);
		if (!env->value)
			return (EXIT_FAILURE);
	}
	env->len += 1;
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
		if ((int)ft_strlen(env->key[i]) == key_len && !ft_strncmp(env->key[i],
				key, key_len))
			return (env->value[i]);
	}
	return (NULL);
}
