#include "../../inc/minishell.h"

void	free_str_arr(char **arr)
{
	int i;

	if(!arr)
		return ;
	i = -1;
	while(arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_jobs(t_jobs *jobs)
{
	if(!jobs)
		return ;
	while(jobs->job_list)
	{
		free_job_list(jobs->job_list);
		jobs->job_list = jobs->job_list->next_job;
	}
	if (jobs->env)
		free_env(jobs->env);
	free(jobs);
}

void	free_job_list(t_job *job_list)
{
	if(!job_list)
		return ;
	if(job_list->args)
		free_str_arr_null(&job_list->args);
	if(job_list->redir)
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
    if(redir->files)
		free_str_arr_null(&redir->files);
	if(redir->eof)
		free_str_arr_null(&redir->eof);
	if(redir->in_f)
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
	if (mshell->envp)
		free(mshell->envp);
	free(mshell);
}
