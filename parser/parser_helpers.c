#include "../minishell.h"

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
