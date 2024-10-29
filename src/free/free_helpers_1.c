#include "../../inc/parser.h"

void	free_jobs(t_jobs *jobs)
{
	if(!jobs)
		return ;
	while(jobs->job_list)
	{
		free_job_list(jobs->job_list);
		jobs->job_list = jobs->job_list->next_job;
	}
	free(jobs);
}

void	free_job_list(t_job *job_list)
{
	if(!job_list)
		return ;
	if(job_list->args)
		free_str_arr(job_list->args);
	if(job_list->redir)
		free_redir(job_list->redir);
    free(job_list);
}

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
    if(redir->files)
		free_str_arr(redir->files);
	if(redir->eof)
		free(redir->eof);
	if(redir->args)
		free(redir->args);
	free(redir);
}

void	free_str_arr(char **arr)
{
	if(!arr)
		return ;
	while(*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
}

void	free_mshell(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->jobs)
		free_jobs(mshell->jobs);
	if (mshell->envp)
		free(mshell->envp);
	if (mshell->prompt)
		free(mshell->prompt);
	if (mshell->path_env)
		free(mshell->path_env);
	if (mshell->cmds)
		free_str_arr(mshell->cmds);
	if (mshell->ctrl_paths)
		free_str_arr(mshell->ctrl_paths);
	if (mshell->success_arr)
		free_str_arr(mshell->success_arr);
}
