#include "parser.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
}

void	free_content(t_cont *content)
{
	if (!content)
		return ;
	if (content->redir)
	{
		if (content->redir->in_filename)
			free_str_arr(content->redir->in_filename);
		if (content->redir->out_filename)
			free_str_arr(content->redir->out_filename);
		free(content->redir);
	}
	if (content->hdoc)
	{
		if (content->hdoc->eof)
			free(content->hdoc->eof);
		if (content->hdoc->args)
			free_str_arr(content->hdoc->args);
		free(content->hdoc);
	}
	free(content);
}

void	free_nodes(t_node *nodes)
{
	if (!nodes)
		return ;
	while (nodes)
	{
		if (nodes->content)
			free_content(nodes->content);
		if (nodes->args)
			free_str_arr(nodes->args);
		nodes = nodes->next;
	}
}

void	free_jobs(t_jobs **jobs)
{
	int	i;

	if (!jobs)
		return ;
	i = -1;
	while (jobs[++i])
	{
		if (jobs[i]->cmd)
			free(jobs[i]->cmd);
		if (jobs[i]->job)
			free(jobs[i]->job);
		if (jobs[i]->job_exec)
			free_str_arr(jobs[i]->job_exec);
		if (jobs[i]->elements)
			free_nodes(jobs[i]->elements);
		free(jobs[i]);
	}
	free(jobs);
}

char	initialize_elements(t_tree *tree)
{
	int	i;

	if (!tree)
		return (-1);
	i = -1;
	while (tree->jobs[++i])
	{
		tree->jobs[i]->elements = ft_calloc(2, sizeof(t_node));
		if (!tree->jobs[i]->elements)
			return (free_jobs(tree->jobs), -1);
	}
	return (0);
}
