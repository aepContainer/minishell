#include "../../inc/minishell.h"

int	get_fd(t_jobs *jobs, t_job *job)
{
	int 	fd;
	int		indexes[4];

	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	fd = 1;
	if (job->redir->files)
	{
		indexes[3] = -1;
		while (job->redir->files[++indexes[3]])
		{
			fd = get_fd_lh(jobs, job, indexes);
			if(indexes[3] >= indexes[2])
				dup2(fd, 1);
			else
				dup2(fd, 0);
		}
	}
	return (fd);
}
