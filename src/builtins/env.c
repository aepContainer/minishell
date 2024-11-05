#include "../../inc/minishell.h"

extern char **environ;

void	env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
}
