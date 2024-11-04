#include "../../inc/minishell.h"

char	ctrl_builtins(char	*cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3)
			&& ft_strlen(cmd) == 3)
		return (pwd());
	return (-1);
}
