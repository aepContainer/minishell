/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:32:49 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:32:50 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo(t_jobs *jobs, t_job *job)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (job->args[1] && !ft_strncmp(job->args[1], "-n", 2)
		&& ft_strlen(job->args[1]) == 2)
	{
		newline = 0;
		i++;
	}
	while (job->args[i])
	{
		ft_putstr_fd(job->args[i], 1);
		if (job->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	jobs->mshell->quest_mark = 0;
}
