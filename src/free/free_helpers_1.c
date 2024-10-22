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

void free_job_list(t_job *job_list)
{
	if(!job)
		return ;
	if(job_list->args)
		free_str_arr(job_list->args); //fonksiyon yaz
	if(job_list->redir)
		free_redir(job_list->redir); //fonksiyon yaz
    free(job_list);
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
