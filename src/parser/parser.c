#include "../../inc/parser.h"

static char	get_redirs(t_jobs *jobs)
{}

char	parser(t_jobs *jobs, char *prompt)
{
	char	**splitted;
	int		i;

	splitted = word_split(prompt);
	if (!splitted)
		return (EXIT_FAILURE);
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			jobs->job_list->next_job = ft_calloc(1, sizeof(t_job));
			if (!jobs->job_list->next_job)
				return (free_jobs(jobs), EXIT_FAILURE);
			jobs->job_list = jobs->job_list->next_job;
		}
		else
		{
			jobs->job_list->args = str_arr_realloc(jobs->job_list->args, splitted[i]);
			if (!jobs->job_list->args)
				return (EXIT_FAILURE);
		}
	}
	return (get_redirs(jobs));
}
