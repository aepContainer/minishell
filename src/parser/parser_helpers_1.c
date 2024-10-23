#include "../../inc/minishell.h"

char	parser(t_jobs *jobs, char *prompt)
{
	t_job	*job_list;
	char	**splitted;
	int		i;

	splitted = str_arr_split(prompt);
	if (!splitted)
		return (-1);
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			jobs->job_list->next_job = &(t_job){0};
			jobs->job_list = jobs->job_list->next_job;
		}
		else
			add_arg(jobs->job_list, splitted[i]);
	}
}
