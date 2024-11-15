#include "../../inc/minishell.h"

static char	distribute(t_jobs *jobs, char **splitted)
{
	t_job	*temp;
	char	redir_status;
	int		i;

	temp = jobs->job_list;
	redir_status = -1;
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			jobs->len += 1;
			temp->next_job = ft_calloc(1, sizeof(t_job));
			if (!temp->next_job)
				return (free_str_arr(splitted), EXIT_FAILURE);
			temp = temp->next_job;
			temp->redir = ft_calloc(1, sizeof(t_redir));
			if (!temp->redir)
				return (free_str_arr(splitted), EXIT_FAILURE);
		}
		else if (handle_distribute(temp, splitted[i], &redir_status))
			return (free_str_arr(splitted), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	parser(t_jobs *jobs, char *prompt)
{
	char	**splitted;

	jobs->job_list = ft_calloc(1, sizeof(t_job));
	if (!jobs->job_list)
		return (EXIT_FAILURE);
	jobs->job_list->redir = ft_calloc(1, sizeof(t_redir));
	if (!jobs->job_list->redir)
		return (free(jobs->job_list), EXIT_FAILURE);
	jobs->len = 1;
	expander(jobs, &prompt);
	splitted = word_split(prompt);
	if (!splitted)
		return (EXIT_FAILURE);
	return (distribute(jobs, splitted));
}
