/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:40 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:47:33 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_special_char(const char *token)
{
	return (ft_strncmp(token, "|", 2) == 0 || ft_strncmp(token, "<", 2) == 0
		|| ft_strncmp(token, ">", 2) == 0 || ft_strncmp(token, "<<", 3) == 0
		|| ft_strncmp(token, ">>", 3) == 0);
}

bool	check_syntax_errors(t_jobs *jobs, char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			if (i == 0 || tokens[i + 1] == NULL || is_special_char(tokens[i + 1]))
			{
				ft_putendl_fd("Syntax error near unexpected token '|'", 2);
				jobs->mshell->quest_mark = 2;
				return (true);
			}
		}
		if (is_special_char(tokens[i]) && ft_strncmp(tokens[i], "|", 2) != 0)
		{
			if (tokens[i + 1] == NULL || is_special_char(tokens[i + 1]))
			{
				ft_putendl_fd("Syntax error near unexpected token", 2);
				jobs->mshell->quest_mark = 2;
				return (true);
			}
		}
	}
	return (false);
}

bool	check_unclosed_quotes(t_jobs *jobs, const char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if ((*input == '\'' || *input == '"') && (quote == '\0'
				|| quote == *input))
		{
			if (!quote)
				quote = *input;
			else
				quote = 0;
		}
		input++;
	}
	if (quote)
	{
		ft_putendl_fd("Syntax error: Unclosed quote", 2);
		jobs->mshell->quest_mark = 2;
		return (true);
	}
	return (false);
}
