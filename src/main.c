#include "../inc/minishell.h"

static void free_nec(t_mshell *mshell)
{
    t_job	*temp;
    t_job	*next;

    temp = mshell->jobs->job_list;
    while (temp)
    {
        next = temp->next_job;
        free_jobs(temp);
        temp = next;
    }
    mshell->jobs->job_list = NULL;
}

static char	process(t_mshell *mshell)
{
	if (parser(mshell->jobs, mshell->prompt))
		return (EXIT_SUCCESS);
	if (executor(mshell))
		return (EXIT_SUCCESS);
	free_nec(mshell);
	return (free(mshell->prompt), EXIT_SUCCESS);
}

static char	get_first_env(t_jobs *jobs, char **env)
{
	char	**splitted;
	int		i;

	jobs->env = ft_calloc(1, sizeof(t_env));
	if (!jobs->env)
		return (EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		splitted = ft_split(env[i], '=');
		if (!splitted)
			return (free_env(jobs->env), EXIT_FAILURE);
		if (env_add(jobs->env, splitted[0], splitted[1]))
			return (free_env(jobs->env), free(splitted), EXIT_FAILURE);
		free(splitted);
	}
	return (EXIT_SUCCESS);
}

static char	init_main(t_mshell *mshell, char **env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	if (!mshell->jobs)
		return (free(mshell), EXIT_FAILURE);
	if (get_first_env(mshell->jobs, env))
		return (free_mshell(mshell), EXIT_FAILURE);
	mshell->jobs->mshell = mshell;
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;
	char		*prompt;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (EXIT_FAILURE);
	if (init_main(mshell, env, argc, argv))
		return (free_mshell(mshell), EXIT_FAILURE);
	while (1)
	{
		prompt = readline(PROMPT);
		if (!prompt)
			return (EXIT_FAILURE);
		set_signal(314159);
		if (*prompt)
			add_history(prompt);
		mshell->prompt = ft_strtrim(prompt, " \t\v\r\f");
		free(prompt);
		if (!mshell->prompt)
			continue ;
		if (process(mshell))
			break ;
	}
	free_mshell(mshell);
	return (EXIT_SUCCESS);
}
