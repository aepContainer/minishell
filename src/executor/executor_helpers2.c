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

static char	*env_find_value_const(t_env *env, const char *key)
{
	int	key_len;
	int	i;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = -1;
	while (env->key[++i])
	{
		if ((int) ft_strlen(env->key[i]) == key_len
				&& !ft_strncmp(env->key[i], key, key_len))
			return (env->value[i]);
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

void	run_cmd(t_jobs *jobs, t_job *job)
{
	char	*exec_path;
	char	*env_path;
	int		i;

	env_path = env_find_value_const(jobs->env, "PATH");
	if (!env_path)
	{
		if (!access(job->args[0], X_OK))
		{
			execve(job->args[0], job->args, jobs->env);
			exit(127);
		}
		else
			error_msg(job->args[0], ": No such file or directory\n");
	}
	exec_path = get_exec_path(job, env_path);
	g_quest_mark = 0;
	execve(exec_path, job->args, jobs->env);
	exit(127);
}
