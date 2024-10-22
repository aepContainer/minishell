#include "../../inc/minishell.h"

void free_jobs(t_jobs *jobs)
{
	if(!jobs)
		return ;
	while(jobs->job_list)
	{
		free_job(jobs->job_list);
		jobs->job_list = jobs->job_list->next_job;
	}
	free(jobs);
}

void free_job(t_job *job)
{
	if(!job)
		return ;
	if(job->args)
		free_str_arr(job->args); //fonksiyon yaz
	if(job->redir)
		free_redir(job->redir); //fonksiyon yaz
    free(job);
}

void free_redir(t_redir *redir)
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

void free_str_arr(char **arr)
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
