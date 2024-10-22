#include "../../inc/minishell.h"


static int	next_quote(char *str, int i, char quote)
{
	while (str[i] != quote)
		i++;
	return (i);
}

char	dist_jobs(t_jobs *jobs, char *prompt)
{
	t_job	*temp;
	int	i;

	jobs->job_list = ft_calloc(1, sizeof(t_job));
	if (!jobs->job_list)
		return (free(jobs), -1);
	jobs->len = 1;
	temp = jobs->job_list;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
		{
			temp->next_job = ft_calloc(1, sizeof(t_job));
			if (!temp->next_job)
				return (free_jobs(jobs), -1);
			temp = temp->next_job;
			jobs->len += 1;
		}
		if (prompt[i] == DQUOTE)
			next_quote(prompt, i, DQUOTE);
		else if (prompt[i] == SQUOTE)
			next_quote(prompt, i, SQUOTE);
	}
	return (0);
}

char	dist_args(t_job *job_list, char *prompt)
{
	char	*temp;
	int		start;
	int		len;
	int		i;

	i = -1;
	while (prompt[++i])
	{
		if(prompt[i] == '|')
			job_list = job_list->next_job;
		if (prompt[i] == DQUOTE)
		{
			start = i;
			len = 0;
			while (prompt[++i] != DQUOTE)
				len++;
		}
		if (prompt[i] == SQUOTE)
		{
			start = i;
			len = 0;
			while (prompt[++i] != SQUOTE)
				len++;
		}
		temp = ft_substr(prompt, start, len);
		if (!temp)
			return (-1);
		job_list->args = str_arr_realloc(job_list->args, temp);
		if (!job_list->args)
			return (-1);
	}
	return (0);
}


int main(void)
{
	
	char prompt[256] = "echo \"selam\" | echo \"iyi\"  | ls -a";
	char prompt2[256] = "echo \"selam\" echo \"iyi\" ls -a";

	t_jobs *jobs;
	jobs = ft_calloc(1,sizeof(t_jobs *));

	dist_jobs(jobs ,prompt);
	while(jobs->job_list)
	{
		dist_args(jobs->job_list,prompt);
		jobs->job_list = jobs->job_list->next_job;

	}

	while(jobs->job_list)
	{
		printf("1\n");
		jobs->job_list = jobs->job_list->next_job;
	}
}