#include "../../inc/minishell.h"

int	get_fd(t_jobs *jobs, t_job *job)
{
	int 	fd;
	int		indexes[5];

	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	indexes[4] = -1;
	fd = 1;
	if (job->redir->files)
	{
		indexes[3] = -1;
		while (job->redir->files[++indexes[3]])
		{
			fd = get_fd_lh(jobs, job, indexes);
			if (fd == -1)
				return (dup2(jobs->mshell->backup[0], 0), close(jobs->mshell->backup[0])
					, dup2(jobs->mshell->backup[1], 1), close(jobs->mshell->backup[1]), -1);
			if(indexes[4] == 1)
				dup2(fd, 1);
			else if (!indexes[4])
				dup2(fd, 0);
		}
	}
	return (fd);
}
