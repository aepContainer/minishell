#include "../minishell.h"

char	ctrl_quote(char *prompt)
{
	char	state;
	int		i;

	state = 0;
	i = -1;
	while (prompt[++i])
	{
		if (!state && (prompt[i] == '\'' || prompt[i] == '\"'))
			state = prompt[i];
		else if (state && (prompt[i] == '\'' || prompt[i] == '\"'))
			state = 0;
	}
	return (state);
}

void	tokenize(t_parse_tree *rtrn, t_mshell *mshell)
{
	t_node	*temp;
	char	**splitted;
	int		i;

	splitted = ft_split(mshell->prompt, ' ');
	if (!splitted)
		return ;
}

t_parse_tree	*parser(t_mshell *mshell)
{
	t_parse_tree	*rtrn;
	int				i;

	if (ctrl_quote(mshell->prompt))
		return (NULL);// Error Control!!
	rtrn = ft_calloc(1, sizeof(t_parse_tree));
	if (!rtrn)
		return (NULL);
	tokenize(rtrn, mshell->prompt);
}
