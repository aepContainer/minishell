#include "../../inc/minishell.h"

char	pwd(void)
{
	char	wd[512];

	if (!getcwd(wd, 512))
	{
		g_quest_mark = 1;
		perror("pwd");
		return (EXIT_FAILURE);
	}
	write(1, wd, ft_strlen(wd));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
