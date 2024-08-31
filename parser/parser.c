#include "../minishell.h"

static char	*get_prompt(int argc, char **argv)
{
	char	*rtrn;
	char	*temp;
	int		i;

	rtrn = ft_strdup(argv[1]);
	if (!rtrn)
		return (NULL);
	i = 1;
	while (++i < argc)
	{
		temp = rtrn;
		rtrn = ft_strjoin(temp, argv[i]);
		free(temp);
		if (!rtrn)
			return (NULL);
		temp = rtrn;
		rtrn = ft_strjoin(temp, " ");
		free(temp);
		if (!rtrn)
			return (NULL);
	}
	return (rtrn);
}

t_ParseTree	*parser(int argc, char **argv, t_mshell *mshell)
{
	t_ParseTree	*rtrn;
	int			i;

	if (!argv)
		return (NULL);
	mshell->prompt = get_prompt(argc, argv);
	if (!mshell->prompt)
		return (NULL);
	if (ctrl_quote(mshell->prompt))
		return (NULL);// Error Control!!
}
