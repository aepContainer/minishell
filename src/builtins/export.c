/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:02 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/22 01:03:13 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	export_errors(t_jobs *jobs, char *arg, const char *msg)
{
	jobs->mshell->quest_mark = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd((char *)msg, 2);
	return (EXIT_FAILURE);
}

static char	validate(char *arg, char state)
{
	char	alpha_state;
	int		i;

	alpha_state = 0;
	i = -1;
	while (arg[++i])
	{
		if (state && arg[i] == '=')
			i++;
		if (ft_isalpha(arg[i]))
			alpha_state = 1;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (EXIT_FAILURE);
	}
	if (!alpha_state)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	export_arg(t_jobs *jobs, char *arg)
{
	char	*key;
	char	*value;
	char	state;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (validate(key, 0))
		return (export_errors(jobs, arg, "not a valid identifier"));
	value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	if (!value)
		return (free(key), EXIT_FAILURE);
	state = update_env(jobs->env, key, value);
	if (state == -1)
		return (free(key), EXIT_FAILURE);
	if (state)
		if (env_add(jobs->env, key, value))
			return (free(key), EXIT_FAILURE);
	return (free(key), EXIT_SUCCESS);
}

static void	print_values(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->len)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key[i], 1);
		if (env->value[i][0])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value[i], 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
	}
}

char	export(t_jobs *jobs, char **args)
{
	int	i;

	if (!args[1])
	{
		print_values(jobs->env);
		jobs->mshell->quest_mark = 0;
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (args[++i])
	{
		if (export_arg(jobs, args[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
