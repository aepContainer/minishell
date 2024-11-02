#include "../../inc/minishell.h"

char	pwd(void)
{
	char	wd[512];

	if (!getcwd(wd, 512))
		return (EXIT_FAILURE);
	write(1, wd, ft_strlen(wd));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
