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

	jobs = ft_calloc(1, sizeof(t_jobs));
	if (!jobs)
		return (-1);
	jobs->jobs = ft_calloc(1, sizeof(t_job));
	if (!jobs->jobs)
		return (free(jobs), -1);
	temp = jobs->jobs;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
		{
			temp->next = ft_calloc(1, sizeof(t_job));
			if (!temp->next)
				return (free_jobs(jobs), -1);
			temp = temp->next;
			jobs->len++;
		}
		if (prompt[i] == DQUOTE)
			next_quote(prompt, i, DQUOTE);
		else if (prompt[i] == SQUOTE)
			next_quote(prompt, i, SQUOTE);
	}
	return (0);
}

char	dist_args(t_job *job, char *prompt)
{
	char	*temp;
	int		start;
	int		len;
	int		i;

	i = -1;
	while (prompt[++i])
	{
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
			return (NULL);
		job->args = str_arr_realloc(job->args, temp);
		free(temp);
		if (!job->args)
			return (NULL);
	}
	return (0);
}
