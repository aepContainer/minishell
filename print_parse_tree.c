#include "minishell.h"

void	print_parse_tree(t_tree *tree, char choice)
{
	int	i;
	int	j;
	printf("tree : %p\ntree->noj : %d\n", tree, tree->noj);
	if (choice)
	{
		i = -1;
		while (tree->env[++i])
			printf("tree->env[%d] : %s\n", i, tree->env[i]);
		printf("\n");
		i = -1;
		while (tree->paths[++i])
			printf("tree->paths[%d] : %s\n", i, tree->paths[i]);
		printf("\n");
		i = -1;
		while (tree->success_arr[++i])
			printf("tree->success_arr[%d] : %s\n", i, tree->success_arr[i]);
	}
	i = -1;
	while (tree->jobs[++i])
	{
		printf("tree->jobs[%d]->cmd : %s\n", i, tree->jobs[i]->cmd);
		printf("tree->jobs[%d]->job : %s\n", i, tree->jobs[i]->job);
		j = -1;
		while (tree->jobs[i]->job_exec[++j])
			printf("tree->jobs[%d]->job_exec[%d] : %s\n", i, j, tree->jobs[i]->job_exec[i]);
		j = -1;
		while (tree->jobs[i]->elements->args[++j])
			printf("tree->jobs[%d]->elements->args[%d] : %s\n", i, j, tree->jobs[i]->elements->args[j]);
	}
}
