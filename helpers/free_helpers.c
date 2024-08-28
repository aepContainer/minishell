#include "../minishell.h"

void	free_and_exit(t_mshell *mshell)
{
	if (!mshell)
		exit();
	if (mshell->envar)
		free_str_arr(mshell->envar);
	if (mshell->history)
		free_str_arr(mshell->history);
	exit();
}
