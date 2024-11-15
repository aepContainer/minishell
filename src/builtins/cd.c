#include "../../inc/minishell.h"

char	cd(char *path)
{
	if (chdir(path) == -1)
	{
		g_quest_mark = 1;
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
