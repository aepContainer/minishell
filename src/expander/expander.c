/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:44 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:33:45 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expander(t_jobs *jobs, char **prompt)
{
	char	*expanded;

	if (!*prompt)
		return ;
	expanded = expand_env_vars(jobs, *prompt);
	if (!expanded)
		return ;
	free(*prompt);
	*prompt = expanded;
}
