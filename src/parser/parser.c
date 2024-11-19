#include "../../inc/minishell.h"

static char	job_init(t_job **temp, char **splitted)
{
	(*temp)->next_job = ft_calloc(1, sizeof(t_job));
	if (!(*temp)->next_job)
		return (free_str_arr(splitted), EXIT_FAILURE);
	*temp = (*temp)->next_job;
	(*temp)->redir = ft_calloc(1, sizeof(t_redir));
	if (!(*temp)->redir)
		return (free_str_arr(splitted), EXIT_FAILURE);
	(*temp)->redir->app_file = -1;
	(*temp)->redir->in_file = -1;
	(*temp)->redir->out_file = -1;
	(*temp)->redir->last_in = 0;
	(*temp)->redir->last_out = 0;
	return (EXIT_SUCCESS);
}

char	distribute(t_mshell *mshell, char **splitted)
{
	t_job	*temp;
	char	redir_status;
	int		i;

	redir_status = -1;
	mshell->jobs->len = 1;
	temp = mshell->jobs->job_list;
	i = -1;
	while (splitted[++i])
	{
		if (splitted[i][0] == '|')
		{
			mshell->jobs->len += 1;
			if (job_init(&temp, splitted))
				return (EXIT_FAILURE);
		}
		else if (handle_distribute(temp, splitted[i], &redir_status))
			return (free_str_arr(splitted), EXIT_FAILURE);
	}
	return (free_str_arr(splitted), EXIT_SUCCESS);
}

char	parser(t_jobs *jobs, char *prompt)
{
	char	**splitted;

	add_history(prompt);
	expander(jobs, &prompt);
	if (!prompt[0] || check_unclosed_quotes(prompt))
		return (EXIT_FAILURE);
	splitted = word_split(prompt);
	free(prompt);
	if (!splitted)
		return (EXIT_FAILURE);
	if (check_syntax_errors(splitted))
		return (EXIT_FAILURE);
	return (distribute(jobs->mshell, splitted));
}
