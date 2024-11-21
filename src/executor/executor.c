/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem <yunozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:29 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/21 20:52:00 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	wait_child(t_mshell *mshell)
{
	t_job	*temp_job;
	int		temp_status;
	int		i;

	temp_job = mshell->jobs->job_list;
	if (mshell->jobs->len == 1 && temp_job->built_in == true)
		return ;
	while (temp_job)
	{
		signal(SIGINT, &handler_sigint);
		i = waitpid(temp_job->pid, &temp_status, 0);
		if (i < 0)
			continue ;
		built_in(temp_job);
		if (mshell->jobs->len == 1 && temp_job->built_in == true)
			break ;
		if (WIFEXITED(temp_status))
			mshell->quest_mark = WEXITSTATUS(temp_status);
		else if (WIFSIGNALED(temp_status))
			mshell->quest_mark = 128 + WTERMSIG(temp_status);
		temp_job = temp_job->next_job;
	}
}

static int	executer_while(t_mshell *mshell, t_job *temp_job)
{
	if (mshell->jobs->len == 1)
	{
		if (temp_job->redir->eof && heredoc(mshell->jobs, temp_job, 1))
			return (0);
		if (no_pipe(mshell->jobs, temp_job))
			return (0);
	}
	else
	{
		if (temp_job->redir->eof && heredoc(mshell->jobs, temp_job, 0))
			return (0);
		if (mshell->quest_mark == 130)
			return (0);
		if (pipe_handle(mshell->jobs, temp_job))
			return (0);
		mshell->quest_mark = 0;
	}
	return (1);
}

void	get_backup(t_mshell *mshell)
{
	dup2(mshell->backup[0], 0);
	close(mshell->backup[0]);
	dup2(mshell->backup[1], 1);
	close(mshell->backup[1]);
}

char	executor(t_mshell *mshell)
{
	t_job	*temp_job;
	int		state;

	state = 1;
	mshell->backup[0] = dup(STDIN_FILENO);
	mshell->backup[1] = dup(STDOUT_FILENO);
	temp_job = mshell->jobs->job_list;
	while (temp_job)
	{
		state = executer_while(mshell, temp_job);
		if (state != 1)
			break ;
		temp_job = temp_job->next_job;
	}
	if (state)
	{
		get_backup(mshell);
		wait_child(mshell);
	}
	return (EXIT_SUCCESS);
}
