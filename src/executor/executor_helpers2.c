#include "../../inc/minishell.h"

static void	run_cmd_error_ctrl(char *path)
{
	t_stat	stat_t;

	stat(path, &stat_t);
	if (S_ISDIR(stat_t.st_mode))
	{
		g_quest_mark = 1;
		error_msg(path, ": Is a directory\n");
		exit(126);
	}
	else if (!S_ISREG(stat_t.st_mode))
	{
		g_quest_mark = 1;
		error_msg(path, ": No such file or directory\n");
		exit(127);
	}
	if (access(path, R_OK))
	{
		g_quest_mark = 1;
		error_msg(path, ":  Permission denied\n");
		exit(126);
	}
}

static char	*accessor(char *env_path, char *cmd)
{
	char	**splitted;
	char	*temp1;
	char	*temp2;
	int		i;

	splitted = ft_split(env_path, ':');
	if (!splitted)
		return (NULL);
	i = -1;
	while (splitted[++i])
	{
		temp1 = ft_strjoin_const(splitted[i], "/");
		temp2 = temp1;
		temp1 = ft_strjoin(temp1, cmd);
		free(temp2);
		if (!temp1)
			return (free_str_arr(splitted), NULL);
		if (!access(temp1, X_OK))
			return (free_str_arr(splitted), temp1);
		free(temp1);
	}
	return (NULL);
}

static char	*get_exec_path(t_job *job, char *env_path)
{
	char	*rtrn;

	if (job->args[0][0] == '/')
	{
		run_cmd_error_ctrl(job->args[0]);
		rtrn = ft_strdup(job->args[0]);
	}
	else
		rtrn = accessor(env_path, job->args[0]);
	if (!rtrn)
	{
		error_msg(job->args[0], ": command not found\n");
		exit(127);
	}
	return (rtrn);
}

static char	**get_env_for_exec(t_env *env)
{
	char	**rtrn;
	char	*arg;
	char	*temp;
	int		i;

	rtrn = NULL;
	i = -1;
	while (++i < env->len)
	{
		arg = ft_strdup(env->key[i]);
		if (!arg)
			return (NULL);
		temp = arg;
		arg = ft_strjoin_const(arg, "=");
		free(temp);
		if (!arg)
			return (NULL);
		temp = arg;
		arg = ft_strjoin_const(arg, env->value[i]);
		free(temp);
		if (!arg)
			return (NULL);
		rtrn = str_arr_realloc(rtrn, arg);
		free(arg);
	}
	return (rtrn);
}

void	run_cmd(t_jobs *jobs, t_job *job)
{
	char	**env;
	char	*exec_path;
	char	*env_path;

	env_path = env_find_value_const(jobs->env, "PATH");
	env = get_env_for_exec(jobs->env);
	//if (!env)
	if (!env_path)
	{
		if (!access(job->args[0], X_OK))
		{
			execve(job->args[0], job->args, env);
			exit(127);
		}
		else
			error_msg(job->args[0], ": No such file or directory\n");
	}
	exec_path = get_exec_path(job, env_path);
	g_quest_mark = 0;
	execve(exec_path, job->args, env);
	exit(127);
}
