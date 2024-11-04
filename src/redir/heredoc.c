#include "../../inc/minishell.h"

static void	read_line(char *buffer)
{
	int		rtrn;
	int		i;

	i = 0;
	while ((rtrn = read(0, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n')
			break;
		i++;
	}
	buffer[i] = '\0';
}

static void	child_process(int fd[2], const char *eof)
{
	char	buffer[1024];

	close(fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		read_line(buffer);
		if (strcmp(buffer, eof) == 0)
			break;
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	exit(0);
}

void	heredoc(char *eof)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return;
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
		child_process(fd, eof);
	else
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}
