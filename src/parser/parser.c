#include "../../inc/minishell.h"

static char	handle_distribute(t_job *job, char *arg)
{
}

char	parser(t_jobs *jobs, char *prompt)
{
	t_job	*temp;
	char	**splitted;
	int		i;

	process_env_vars(jobs->env, &prompt);
	splitted = word_split(prompt);
	if (!splitted)
		return (free_jobs(jobs), EXIT_FAILURE);
	temp = jobs->job_list;
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			temp->next_job = ft_calloc(1, sizeof(t_job));
			if (!temp->next_job)
				return (free_jobs(jobs), EXIT_FAILURE);
			temp = temp->next_job;
		}
		else if (handle_distribute(temp, splitted[i]))
			return (free_jobs(jobs), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
