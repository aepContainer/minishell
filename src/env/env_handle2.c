#include "../../inc/minishell.h"

char	get_first_env(t_jobs *jobs, char **env)
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