#include "../inc/minishell.h"

static char	nuller(t_mshell *mshell)
{
	t_job	*temp;
	t_job	*next;

	temp = mshell->jobs->job_list;
	if (temp)
	{
		
		while (temp)
		{
			next = temp->next_job;
			free_job_list(temp);
			temp = next;
		}
		mshell->jobs->job_list = NULL;	
	}
	mshell->jobs->job_list = ft_calloc(1, sizeof(t_job));
	if(!mshell->jobs->job_list)
		return (EXIT_FAILURE);
	mshell->jobs->job_list->redir = ft_calloc(1, sizeof(t_redir));
	if(!mshell->jobs->job_list->redir)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	mshell_init(t_mshell *mshell, char **env)
{
	g_quest_mark = 0;
	mshell->exit = 0;
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	if (!mshell->jobs)
		return (EXIT_FAILURE);
	if (get_first_env(mshell->jobs, env))
		return (EXIT_FAILURE);
	mshell->jobs->mshell = mshell;
	return (EXIT_SUCCESS);
}

static char	process(t_mshell *mshell, char *prompt)
{
	if(parser(mshell->jobs, prompt))
		return (EXIT_FAILURE);
	if(executor(mshell))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	start_mshell(t_mshell *mshell)
{
	char	*prompt;

	while (1)
	{
		nuller(mshell);
		set_signal(MAIN);
		prompt = readline("shellshock <(o_o)> ");
		if (!prompt)
		{
			free(prompt);
			break ;
		}
		if (process(mshell, prompt))
			continue ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;

	(void)argv;
	if (argc != 1)
		return (1);
	mshell = ft_calloc(1,sizeof(t_mshell));
	if(!mshell)
		return (EXIT_FAILURE);
	if(mshell_init(mshell, env))
		return (EXIT_FAILURE);
	start_mshell(mshell);
	free_mshell(mshell);
	return (0);
}
