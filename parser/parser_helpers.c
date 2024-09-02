#include "../minishell.h"

t_node	*new_token(char *input, char type)
{
	t_node	*rtrn;

	if (type == -1)
		return (NULL);
	rtrn = ft_calloc(1, sizeof(t_node));
	if (!rtrn)
		return (NULL);
	rtrn->type = type;
	if (rtrn->type == CMD)
		rtrn->content.cmd = input;
	else if (rtrn->type == ARG)
		add_arg(&rtrn->content.args, input);
//	yapıdaki değerlere değer atamaya devam et!
	if (ft_strnstr(input, "|", ft_strlen(input)))
		rtrn->content.pipe = 1;
	return (rtrn);
}

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
