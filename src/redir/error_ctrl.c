/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:18 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:19 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_msg(t_jobs *jobs, char *file, const char *message)
{
	jobs->mshell->quest_mark = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd((char *)message, 2);
}

char	redir_error(t_jobs *jobs, t_job *job, char *file_i, int fd)
{
	t_stat	stat_t;

	if (fd == -1)
	{
		jobs->mshell->quest_mark = 1;
		stat(file_i, &stat_t);
		if (S_ISDIR(stat_t.st_mode))
			error_msg(jobs, file_i, ": Is a directory\n");
		else if (!S_ISDIR(stat_t.st_mode))
			error_msg(jobs, file_i, ": No such file or directory\n");
		if (jobs->len == 1)
			return (EXIT_FAILURE);
		if (jobs->len != 1 || job->built_in == false)
			exit(1);
	}
	return (EXIT_SUCCESS);
}
