#include "../inc/minishell.h"

/*
static void	nuller(t_mshell *mshell)
{
	if (mshell->cmds)
		free_str_arr(mshell->cmds);
	mshell->cmds = NULL;
	if (mshell->ctrl_paths)
		free_str_arr(mshell->ctrl_paths);
	mshell->ctrl_paths = NULL;
	if (mshell->envp)
		free_str_arr(mshell->envp);
	if (mshell->success_arr)
		free_str_arr(mshell->success_arr);
	mshell->success_arr = NULL;
}
*/

static char	process(t_mshell *mshell)
{
	char	*prompt;

	prompt = readline(PROMPT);
	if (!prompt)
		return (EXIT_FAILURE);
	if (*prompt)
		add_history(prompt);
	mshell->prompt = ft_strtrim(prompt, " \t\v\r\f");
	free(prompt);
	if (!mshell->prompt)
		return (EXIT_FAILURE);// continue ;
	if (parser(mshell->jobs, mshell->prompt))
		return (EXIT_FAILURE);
	if (executor(mshell))
		return (EXIT_FAILURE);
	//nuller(mshell);
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
		if (env_add(jobs->env, splitted[0], splitted[1]))
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
	mshell->jobs->mshell = mshell;
	if (get_first_env(mshell->jobs, env))
		return (free_mshell(mshell), EXIT_FAILURE);
	while (1)
		if (process(mshell))
			break ;
	free_mshell(mshell);
	return (EXIT_SUCCESS);
}
