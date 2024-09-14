#include "../minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	free_mshell(t_mshell *mshell)
{
	if (!mshell)
		return ;
	if (mshell->envar)
		free_str_arr(mshell->envar);
	if (mshell->history)
		free_str_arr(mshell->history);
	if (mshell->prompt)
		free(mshell->prompt);
}

void	free_tree(t_tree *tree)
{
	int	i;

	if (!tree)
		return ;
	while (tree)
	{
		if (tree->job)
		{
			if (tree->job->job)
				free_args(tree->job->job);
			if (tree->job->elements)
			{
				i = -1;
				while (tree->job->elements[++i])
					free_node(tree->job->elements[i]);
				free(tree->job->elements);
			}
		}
		free(tree);
		tree = tree->next;
	}
}

void	free_node(t_node *node_list)
{
	if (!node_list)
		return ;
	while (node_list)
	{
		if (node_list->content.args)
			free_args(node_list->content.args);
		if (node_list->content.cmd)
			free(node_list->content.cmd);
		if (node_list->content.envar)
			free(node_list->content.envar);
		free(node_list);
		node_list = node_list->next;
	}
}
