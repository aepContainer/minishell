/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:42 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/21 20:36:52 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_quote_state(t_quote_state *state, char c)
{
	if (c == '\'' && !state->in_double)
		state->in_single = !state->in_single;
	else if (c == '\"' && !state->in_single)
		state->in_double = !state->in_double;
}

static int	calc_len_helper_lh(t_jobs *jobs, char *prompt, int *index)
{
	char	*key;
	char	*value;
	int		start;
	int		len;

	len = 0;
	start = *index;
	while (ft_isalnum(prompt[*index]) || prompt[*index] == '_')
		(*index)++;
	key = ft_substr(prompt, start, *index - start);
	if (!key)
		return (0);
	value = NULL;
	value = env_find_value(jobs->env, key);
	if (value)
		len += ft_strlen(value);
	free(key);
	return (len);
}

static int	calc_len_helper(t_jobs *jobs, char *prompt, int *index)
{
	int		len;
	char	*temp;

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
		len += calc_len_helper_lh(jobs, prompt, index);
	return (len);
}

int	calc_len(t_jobs *jobs, char *prompt, t_quote_state state)
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
			len += calc_len_helper(jobs, prompt, &index);
		else
		{
			len++;
			index++;
		}
	}
	return (len);
}
