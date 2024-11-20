/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:20 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:21 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	get_first_env(t_jobs *jobs, char **env)
{
	char	**splitted;
	int		i;

	jobs->env = ft_calloc(1, sizeof(t_env));
	if (!jobs->env)
		return (EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		splitted = ft_split(env[i], '=');
		if (!splitted)
			return (free_env(jobs->env), EXIT_FAILURE);
		if (env_add(jobs->env, splitted[0], splitted[1]))
			return (free_env(jobs->env), free(splitted), EXIT_FAILURE);
		free_str_arr(splitted);
	}
	return (EXIT_SUCCESS);
}

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

static char	env_del_index_lh(t_env **env, t_env *temp, int index)
{
	char	state;
	int		i;

	state = 0;
	i = -1;
	while (++i < temp->len)
	{
		if (i == index)
		{
			free((*env)->key[i]);
			free((*env)->value[i]);
			state = 1;
		}
		temp->key[i] = ft_strdup((*env)->key[i + state]);
		if (!temp->key[i])
			return (free_env(temp), EXIT_FAILURE);
		temp->value[i] = ft_strdup((*env)->value[i + state]);
		if (!temp->value[i])
			return (free_env(temp), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	env_del_index(t_env **env, int index)
{
	t_env	*temp;

	temp = ft_calloc(1, sizeof(t_env));
	if (!temp)
		return (EXIT_FAILURE);
	temp->len = (*env)->len - 1;
	if (calloc_key_value(&temp->key, &temp->value, temp->len + 1))
		return (EXIT_FAILURE);
	if (env_del_index_lh(env, temp, index))
		return (EXIT_FAILURE);
	free_env(*env);
	*env = temp;
	return (EXIT_SUCCESS);
}
