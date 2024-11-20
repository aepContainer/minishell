#include "../../inc/minishell.h"


void	echo(t_job *job)
{
	int		i;
	int		newline;

	newline = 1;
	i = 1;
	if (job->args[1] && !ft_strncmp(job->args[1], "-n", 2)
		&& ft_strlen(job->args[1]) == 2)
	{
		newline = 0;
		i++;
	}
	while (job->args[i])
	{
		ft_putstr_fd(job->args[i], 1);
		if (job->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
