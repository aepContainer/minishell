#include "../../inc/minishell.h"

static void	echo_line_helper(char *str, bool *in_quote, char *quote_type)
{
	int		j;

	j = -1;
	while (str[++j])
	{
		if (ft_strchr(QUOTES, str[j]))
		{
			if (!*in_quote)
			{
				*quote_type = str[j];
				*in_quote = true;
			}
			else if (str[j] == *quote_type)
				*in_quote = false;
			else if (*in_quote)
				ft_putchar_fd(str[j], 1);
		}
		else
			ft_putchar_fd(str[j], 1);
	}
}

void	echo(t_job *job)
{
	int		i;
	int		newline;
	bool	in_quote;
	char	quote_type;

	newline = 1;
	in_quote = false;
	i = 1;
	if (job->args[1] && !ft_strncmp(job->args[1], "-n", 2)
		&& ft_strlen(job->args[1]) == 2)
	{
		newline = 0;
		i++;
	}
	while (job->args[i])
	{
		echo_line_helper(job->args[i], &in_quote, &quote_type);
		if (job->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
