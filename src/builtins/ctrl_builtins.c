#include "../../inc/minishell.h"

void	built_in(t_job *job)
{
	if (!ft_strncmp(job->args[0], "pwd", 3)
			&& ft_strlen(job->args[0]) == 3)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "cd", 2) && ft_strlen(job->args[0]) == 2)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "echo", 4) && ft_strlen(job->args[0]) == 4)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "env", 3) && ft_strlen(job->args[0]) == 3)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "exit", 4) && ft_strlen(job->args[0]) == 4)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "unset", 5) && ft_strlen(job->args[0]) == 5)
		job->built_in = true;
	else if (!ft_strncmp(job->args[0], "export", 6) && ft_strlen(job->args[0]) == 6)
		job->built_in = true;
	else
		job->built_in = false;
}

char	ctrl_builtins(t_jobs *jobs, t_job *job)
{
	char	state;

	if (!ft_strncmp(job->args[0], "pwd", 3)
			&& ft_strlen(job->args[0]) == 3)
	{
		g_quest_mark = pwd();
		return (g_quest_mark);
	}
	else if (!ft_strncmp(job->args[0], "cd", 2) && ft_strlen(job->args[0]) == 2)
	{
		g_quest_mark = cd(job->args[1]);
		return (g_quest_mark);
	}
	else if (!ft_strncmp(job->args[0], "echo", 4) && ft_strlen(job->args[0]) == 4)
	{
		echo(job);
		g_quest_mark = 0;
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(job->args[0], "env", 3) && ft_strlen(job->args[0]) == 3)
	{
		env(jobs->env);
		g_quest_mark = 0;
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(job->args[0], "exit", 4) && ft_strlen(job->args[0]) == 4)
	{
		exit_d(job->args);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(job->args[0], "unset", 5) && ft_strlen(job->args[0]) == 5)
	{
		unset(&jobs->env, job->args);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(job->args[0], "export", 6) && ft_strlen(job->args[0]) == 6)
	{
		state = export(jobs->env, job->args);
		return (state);
	}
	return (-1);
}
