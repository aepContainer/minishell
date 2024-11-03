#include "../inc/minishell.h"

static char	*read_prompt(void)
{
	char	*rtrn;

	rtrn = readline(PROMPT);
	if (!rtrn)
		return (NULL);
	if (*rtrn)
		add_history(rtrn);
	return (rtrn);
}

static char	process(t_mshell *mshell)
{
	char	*prompt;

	prompt = read_prompt();
	mshell->prompt = ft_strtrim(prompt, " \t\v\r\f");
	free(prompt);
	if (!mshell->prompt)
		return (EXIT_FAILURE);
	if (parser(mshell->jobs, mshell->prompt))
		return (EXIT_FAILURE);
	if (executor(mshell))
		return (EXIT_FAILURE);
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
			return (free_env_node(jobs->env), EXIT_FAILURE);
		if (env_add(&jobs->env, splitted[0], splitted[1]))
			return (free_env_node(jobs->env), free(splitted), EXIT_FAILURE);
		free(splitted);
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;

	(void)argc;
	(void)argv;
	mshell = ft_calloc(1, sizeof(t_mshell));
	if (!mshell)
		return (EXIT_FAILURE);
	mshell->jobs = ft_calloc(1, sizeof(t_jobs));
	if (!mshell->jobs)
		return (free(mshell), EXIT_FAILURE);
	if (!get_first_env(mshell->jobs, env))
		return (free_mshell(mshell), EXIT_FAILURE);
	signal_handle_general(mshell);
	while (1)
		if (process(mshell))
			break ;
	free_mshell(mshell);
	//quitting(mshell);
	return (EXIT_SUCCESS);
}
