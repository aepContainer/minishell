#include "../../inc/minishell.h"

void	error_msg(char *file, const char *message)
{
	g_quest_mark = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd((char *) message, 2);
}

char	redir_error(t_jobs *jobs, t_job *job, char *file_i, int fd)
{
	t_stat	stat_t;

	if (fd == -1)
	{
		g_quest_mark = 1;
		stat(file_i, &stat_t);
		if (S_ISDIR(stat_t.st_mode))
			error_msg(file_i, ": Is a directory\n");
		else if (!S_ISDIR(stat_t.st_mode))
			error_msg(file_i, ": No such file or directory\n");
		if (jobs->len == 1)
			return (EXIT_FAILURE);
		if (jobs->len != 1 || job->built_in == false)
			exit(1);
	}
	return (EXIT_SUCCESS);
}
