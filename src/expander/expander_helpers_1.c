/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:34 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:35 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	calc_len_helper(t_jobs *jobs, char *prompt, int *index)
{
	int		len;
	char	*key;
	char	*value;
	char	*temp;
	int		start;

	len = 0;
	(*index)++;
	if (prompt[*index] == '?')
	{
		temp = ft_itoa(jobs->mshell->quest_mark);
		if (!temp)
			return (0);
		len += ft_strlen(temp);
		free(temp);
	}
	else
	{
		start = *index;
		while (ft_isalnum(prompt[*index]) || prompt[*index] == '_')
			(*index)++;
		key = ft_substr(prompt, start, *index - start);
		value = env_find_value(jobs->env, key);
		if (value)
			len += ft_strlen(value);
		free(key);
	}
	return (len);
}

static void	expand_variable(char *prompt, char *result, t_jobs *jobs,
		int *temps)
{
	char	*key;
	char	*value;
	int		start;

	start = temps[0];
	while (ft_isalnum(prompt[start]) || prompt[start] == '_')
		start++;
	key = ft_substr(prompt, temps[0], start - temps[0]);
	value = env_find_value(jobs->env, key);
	free(key);
	if (value)
	{
		ft_strlcpy(result + temps[1], value, ft_strlen(value) + 1);
		temps[1] += ft_strlen(value);
	}
	temps[0] = start;
}

static void	process_variable(char *prompt, char *result, t_jobs *jobs,
		int *temps)
{
	char	*value;

	temps[0]++;
	if (prompt[temps[0]] == 0)
		result[temps[1]++] = '$';
	else if (prompt[temps[0]] == '?')
	{
		value = ft_itoa(jobs->mshell->quest_mark);
		if (!value)
			return ;
		ft_strlcpy(result + temps[1], value, ft_strlen(value) + 1);
		temps[1] += ft_strlen(value);
		free(value);
		temps[0]++;
	}
	else if (ft_isalnum(prompt[temps[0]]) || prompt[temps[0]] == '_')
		expand_variable(prompt, result, jobs, temps);
	else
		result[temps[1]++] = '$';
}

static int	calc_len(t_jobs *jobs, char *prompt, t_quote_state state)
{
	int	len;
	int	index;

	len = 0;
	state.in_single = false;
	state.in_double = false;
	index = 0;
	while (prompt[index])
	{
		update_quote_state(&state, prompt[index]);
		if (prompt[index] == '$' && !state.in_single)
		{
			len += calc_len_helper(jobs, prompt, &index);
			index++;
		}
		else
		{
			len++;
			index++;
		}
	}
	return (len);
}

char	*expand_env_vars(t_jobs *jobs, char *prompt)
{
	t_quote_state	state;
	char			*result;
	int				*temps;

	if (!prompt)
		return (NULL);
	temps = ft_calloc(3, sizeof(int));
	if (!temps)
		return (NULL);
	state = (t_quote_state){false, false};
	temps[2] = calc_len(jobs, prompt, state);
	result = ft_calloc(1, temps[2] + 1);
	if (!result)
		return (free(temps), NULL);
	while (prompt[temps[0]])
	{
		update_quote_state(&state, prompt[temps[0]]);
		if (prompt[temps[0]] == '$' && !state.in_single)
			process_variable(prompt, result, jobs, temps);
		else
			result[temps[1]++] = prompt[temps[0]++];
	}
	result[temps[1]] = 0;
	return (free(temps), result);
}
