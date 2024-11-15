#include "../../inc/minishell.h"

void	echo(t_job *job)
{
	int	i;
	int	j;
	int	newline;
	char	quote_type;
	bool	in_quote;

	newline = 1;
	in_quote = false;
	i = 1;
	if (job->args[1] && ft_strncmp(job->args[1], "-n", 2) == 0
		&& ft_strlen(job->args[1]) == 2)
	{
		newline = 0;
		i++;
	}
	while (job->args[i])
	{
		j = 0;
		while (job->args[i][j])
		{
			if (ft_strchr(QUOTES, job->args[i][j]))
			{
				if (!in_quote)
				{
					quote_type = job->args[i][j];
					in_quote = !in_quote;
				}
				else
				{
					if (job->args[i][j] == quote_type)
						in_quote = !in_quote;
				}
			}
			if (job->args[i][j] != quote_type)
				write(1, &job->args[i][j], 1);
			j++;
		}
		if (job->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
