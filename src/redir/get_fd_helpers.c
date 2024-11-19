#include "../../inc/minishell.h"

static int	open_out(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->out_file = fd;
	return (fd);
}

static int	open_app(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->app_file = fd;
	return (fd);
}

static int	open_in(t_jobs *jobs, t_job *job, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (file_control(jobs, job, file, fd))
		return (-1);
	job->redir->in_file = fd;
	return (fd);
}

static char	get_fd_lh_if(char **address, char *ctrl_str, char *file, int len1)
{
	int	len2;

	len2 = ft_strlen(ctrl_str);
	return(address && !ft_strncmp(file, ctrl_str, len1) && len1 == len2);
}

int	get_fd_lh(t_jobs *jobs, t_job *job, int *indexes)
{
	int		fd;
	char	*file;

	fd = 1;
	file = NULL;
	if (job->redir->files)
		file = job->redir->files[indexes[3]];
	if (job->redir->out_f && get_fd_lh_if(job->redir->out_f
		, job->redir->out_f[indexes[0]], file,ft_strlen(file)))
		fd = open_out(jobs, job, job->redir->out_f[indexes[0]++]);
	else if (job->redir->app_f && get_fd_lh_if(job->redir->app_f
		, job->redir->app_f[indexes[1]], file,ft_strlen(file)))
		fd = open_app(jobs, job, job->redir->app_f[indexes[1]++]);
	else if (job->redir->in_f && get_fd_lh_if(job->redir->in_f
		, job->redir->in_f[indexes[2]], file,ft_strlen(file)))
		fd = open_in(jobs, job, job->redir->in_f[indexes[2]++]);
	return (fd);
}
