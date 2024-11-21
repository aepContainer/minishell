/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:33:50 by apalaz            #+#    #+#             */
/*   Updated: 2024/11/22 00:48:44 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_jobs(t_jobs *jobs)
{
	t_job	*temp1;
	t_job	*temp2;

	if (!jobs)
		return ;
	if (jobs->job_list)
	{
		temp1 = jobs->job_list;
		while (temp1)
		{
			temp2 = temp1->next_job;
			free_job_list(temp1);
			temp1 = temp2;
		}
	}
	if (jobs->env)
		free_env(jobs->env);
	free(jobs);
}

void	free_job_list(t_job *job_list)
{
	if (!job_list)
		return ;
	if (job_list->args)
		free_str_arr_null(&job_list->args);
	if (job_list->redir)
	{
		free_redir(job_list->redir);
		job_list->redir = NULL;
	}
	free(job_list);
}

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->files)
		free_str_arr_null(&redir->files);
	if (redir->eof)
		free_str_arr_null(&redir->eof);
	if (redir->in_f)
		free_str_arr_null(&redir->in_f);
	if (redir->out_f)
		free_str_arr_null(&redir->out_f);
	if (redir->app_f)
		free_str_arr_null(&redir->app_f);
	free(redir);
}

void	free_mshell(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->jobs)
		free_jobs(mshell->jobs);
	free(mshell);
}
