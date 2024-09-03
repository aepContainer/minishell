#include "../minishell.h"

static char	add_node_to_tree_helper(t_tree *tree, t_node *node)
{
	t_node	*temp;
	int		len;
	int		i;

	temp = node;
	len = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			break;
		temp = temp->next;
		len++;
	}
	tree->elements = ft_calloc(len + 1, sizeof(t_node *));
	if (!tree->elements)
		return (-1);
	temp = node;
	i = -1;
	while (++i < len)
	{
		tree->elements[i] = temp;
		temp = temp->next;
	}
	return (0);
}

char	add_node_to_tree(t_mshell *mshell, t_tree *tree, t_node *node)
{
	t_tree	*temp;
	int		i;

	add_node_to_tree_helper(tree, node);
	i = 0;
	while (++i < mshell->nop)
	{
		temp->next = ft_calloc(1, sizeof(t_tree));
		if (!temp->next)
			return (-1);
		temp = temp->next;
		add_node_to_tree_helper(temp, node);
		while (node->content.pipe == 0)
			node = node->next;
		node = node->next;
	}
	mshell->parsed = ft_calloc(mshell->nop, sizeof(t_tree));
	if (!mshell->parsed)
		return (-1);
	mshell->parsed = tree;
	return (0);
}

char	inject_jobs(t_tree *tree, t_node *node)
{
//	jobs değerlerini ata!
}

void	add_arg(char ***args, char *arg)
{
	char	**new_args;
	int		i;

	if (!*args)
	{
		new_args = ft_calloc(2, sizeof(char *));
		if (!new_args)
			return ;
		new_args[0] = arg;
		free_args(*args);
		*args = &new_args;
		return ;
	}
	i = 0;
	while ((*args)[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return ;
	i = -1;
	while ((*args)[++i])
		new_args[i] = (*args)[i];
	new_args[i] = arg;
	free_args(*args);
	*args = &new_args;
}
