/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:05 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:44:41 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	check_redir(char **redir_list, char *arg_trimmed)
{
	int	len_str;
	int	len_arg;
	int	len;

	if (!redir_list)
		return (EXIT_SUCCESS);
	len = str_arr_len(redir_list);
	len_arg = ft_strlen(arg_trimmed);
	len_str = ft_strlen(redir_list[len - 1]);
	if (!ft_strncmp(redir_list[len - 1], arg_trimmed, len_str)
		&& len_str == len_arg)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	ctrl_append(t_redir *redir, char *arg)
{
	char	*trimmed;

	trimmed = ft_strtrim(arg, "\"");
	if (!trimmed)
		return (1);
	if (check_redir(redir->app_f, trimmed) || check_redir(redir->in_f, trimmed)
		|| check_redir(redir->out_f, trimmed) || check_redir(redir->eof,
			trimmed))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}
