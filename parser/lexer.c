#include "parser.h"

char	lexer(char *str)
{
	int	len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	if (!ft_strncmp(str, "echo", len) || !ft_strncmp(str, "cd", len)
		|| !ft_strncmp(str, "pwd", len) || !ft_strncmp(str, "export", len)
		|| !ft_strncmp(str, "unset", len) ||!ft_strncmp(str, "env", len)
		|| !ft_strncmp(str, "exit", len))
		return (BLTNS);
	else if (str[0] == '\'' || str[0] == '\"' || !ft_strncmp(str, "-n", len))
		return (ARG);
	else if (str[0] == '|' && !str[1])
		return (PIPE);
	else if (((str[0] == '<' && str[1] == '<')
			|| str[0] == '>' && str[1] == '>') && !str[2])
		return (HDOC);
	else if (str[0] == '$')
		return (ENVAR);
	return (NONE);
}
