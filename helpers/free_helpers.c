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
