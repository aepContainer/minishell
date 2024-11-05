#include "../../inc/minishell.h"

void	exit_d(char **args)
{
	int	exit_status;

	if (args[1])
	{
		if (args[2])
		{
			ft_printf("exit: too many arguments\n");
			return ;
		}
		exit_status = ft_atoi(args[1]);
		if (exit_status == 0 && args[1][0] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n", args[1]);
			exit_status = 255;
		}
	}
	else
		exit_status = 0;
	ft_printf("exit\n");
	exit(exit_status);
}
