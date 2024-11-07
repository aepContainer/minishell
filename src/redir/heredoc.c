#include "../../inc/minishell.h"

static char	*child_process(int fd[2], const char *eof)
{
	char	*arg;
	char	*temp;
	char	*buffer;
	int		len[2];

	close(fd[0]);
	buffer = readline(">");
	while (!buffer)
		readline(">");
	len[0] = ft_strlen(buffer);
	len[1] = ft_strlen(eof);
	while (!ft_strncmp(buffer, eof, len[0]) && len[0] == len[1])
	{
		temp = arg;
		arg = ft_strjoin(arg, buffer);
		free(temp);
		free(buffer);
		if (!arg)
			return (NULL);
		buffer = readline(">");
		while (!buffer)
			readline(">");
		len[0] = ft_strlen(buffer);
	}
	return (close(fd[1]), arg);
}

char	*heredoc(char **eof)
{
	char	*arg;
	pid_t	pid;
	int		fd[2];
	int		i;

	arg = NULL;
	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid < 0)
		return (NULL);
	if (pid == 0)
	{
		i = -1;
		while (eof[++i])
			arg = ft_strjoin(arg, child_process(fd, eof[i]));
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	return (arg);
}
