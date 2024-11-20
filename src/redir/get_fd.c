/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:22 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:23 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_fd_init(int indexes[4])
{
	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	indexes[4] = -1;
}

int	get_fd(t_jobs *jobs, t_job *job)
{
	int	fd;
	int	indexes[5];

	fd = 1;
	get_fd_init(indexes);
	if (job->redir->files)
	{
		indexes[3] = -1;
		while (job->redir->files[++indexes[3]])
		{
			fd = get_fd_lh(jobs, job, indexes);
			if (fd == -1)
				return (dup2(jobs->mshell->backup[0], 0),
					close(jobs->mshell->backup[0]),
					dup2(jobs->mshell->backup[1], 1),
					close(jobs->mshell->backup[1]), -1);
			if (indexes[4] == 1)
				dup2(fd, 1);
			else if (!indexes[4])
				dup2(fd, 0);
			if (fd != 1)
				close(fd);
		}
	}
	return (fd);
}
