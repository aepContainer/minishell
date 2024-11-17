#include "../../inc/minishell.h"

static int	file_handle(char *ctrl_str, char **files, int *index, char *state)
{
	size_t	len;
	size_t	len_f;
	int		fd;

	if (files)
	{
		len = ft_strlen(ctrl_str);
		len_f = ft_strlen(files[*index]);
		if (!ft_strncmp(ctrl_str, files[*index], len) && len == len_f)
		{
			if (state[1] == 0)
				fd = open(files[*index], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (state[1] == 1)
				fd = open(files[*index], O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(files[*index], O_RDONLY, 0644);
			(void)*index++;
			if (state[1] == 0 || state[1] == 1)
				state[0] = 1;
			else
				state[0] = 0;
			return (fd);
		}
	}
	return (1);
}

static int	*init_get_fd(char *state)
{
	int	*indexes;

	if (!state)
		return (NULL);
	indexes = ft_calloc(4, sizeof(int));
	if (!indexes)
		return (NULL);
	state[0] = 0;
	state[2] = 0;
	return (indexes);
}

static int	get_fd_line_helper1(t_jobs *jobs, t_job *job, int *indexes, char *state)
{
	int	fd;

	state[1] = 0;
	fd = file_handle(job->redir->files[indexes[3]], job->redir->out_f, indexes, state);
	if (fd != 1 && file_control(jobs, job, job->redir->out_f[indexes[0]], fd))
		return (-1);
	if (state[2] == 1)
	{
		state[1] = 1;
		if (fd == 1)
			fd = file_handle(job->redir->files[indexes[3]], job->redir->app_f, indexes + 1, state);
		if (fd != 1 && file_control(jobs, job, job->redir->app_f[indexes[1]], fd))
			return (-1);
		if (state[2] == 1)
		{
			state[1] = 2;
			if (fd == 1)
				fd = file_handle(job->redir->files[indexes[3]], job->redir->in_f, indexes + 2, state);
			if (fd != 1 && file_control(jobs, job, job->redir->in_f[indexes[2]], fd))
				return (-1);
		}
	}
	return (1);
}

static int	get_fd_line_helper2(char *state, int fd)
{
	if (fd == -1)
	{
		g_quest_mark = 1;
		return (EXIT_FAILURE);
	}
	if (state[0])
		dup2(fd, 1);
	else
		dup2(fd, 0);
	close(fd);
	return (EXIT_SUCCESS);
}

int	get_fd(t_jobs *jobs, t_job *job)
{
	char	*state;
	int 	fd;
	int		*indexes;

	state = ft_strdup("aaa");
	indexes = init_get_fd(state);
	if (!indexes)
		return (-1);
	fd = 1;
	if (job->redir->files)
	{
		indexes[3] = -1;
		while (job->redir->files[++indexes[3]])
		{
			fd = get_fd_line_helper1(jobs, job, indexes, state);
			if (get_fd_line_helper2(state, fd))
				return (-1);
		}
	}
	return (fd);
}
