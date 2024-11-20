/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:34:20 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/20 21:34:21 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_out(t_jobs *jobs, t_job *job, char *file, int indexes[5])
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (access(file, F_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": No such file or directory\n");
		return (-1);
	}
	if (access(file, W_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": Permission denied\n");
		return (-1);
	}
	if (redir_error(jobs, job, file, fd))
		return (-1);
	job->redir->out_file = fd;
	indexes[4] = 1;
	return (fd);
}

static int	open_app(t_jobs *jobs, t_job *job, char *file, int indexes[5])
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (access(file, F_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": No such file or directory\n");
		return (-1);
	}
	if (access(file, W_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": Permission denied\n");
		return (-1);
	}
	if (redir_error(jobs, job, file, fd))
		return (-1);
	job->redir->app_file = fd;
	indexes[4] = 1;
	return (fd);
}

static int	open_in(t_jobs *jobs, t_job *job, char *file, int indexes[5])
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (access(file, F_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": No such file or directory\n");
		return (-1);
	}
	if (access(file, R_OK))
	{
		jobs->mshell->quest_mark = 1;
		error_msg(jobs, file, ": Permission denied\n");
		return (-1);
	}
	if (redir_error(jobs, job, file, fd))
		return (-1);
	job->redir->in_file = fd;
	indexes[4] = 0;
	return (fd);
}

static char	get_fd_lh_if(char *ctrl_str, char *file, int len1)
{
	int	len2;

	if (!ctrl_str)
		return (-1);
	len2 = ft_strlen(ctrl_str);
	return (!ft_strncmp(file, ctrl_str, len1) && len1 == len2);
}

int	get_fd_lh(t_jobs *jobs, t_job *job, int indexes[5])
{
	int		fd;
	char	*file;

	fd = 1;
	file = NULL;
	if (job->redir->files)
		file = job->redir->files[indexes[3]];
	if (job->redir->out_f && get_fd_lh_if(job->redir->out_f[indexes[0]], file,
			ft_strlen(file)) != -1)
		fd = open_out(jobs, job, job->redir->out_f[indexes[0]++], indexes);
	else if (job->redir->app_f && get_fd_lh_if(job->redir->app_f[indexes[1]],
			file, ft_strlen(file)) != -1)
		fd = open_app(jobs, job, job->redir->app_f[indexes[1]++], indexes);
	else if (job->redir->in_f && get_fd_lh_if(job->redir->in_f[indexes[2]],
			file, ft_strlen(file)) != -1)
		fd = open_in(jobs, job, job->redir->in_f[indexes[2]++], indexes);
	return (fd);
}
